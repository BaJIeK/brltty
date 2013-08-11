/*
 * BRLTTY - A background process providing access to the console screen (when in
 *          text mode) for a blind person using a refreshable braille display.
 *
 * Copyright (C) 1995-2012 by The BRLTTY Developers.
 *
 * BRLTTY comes with ABSOLUTELY NO WARRANTY.
 *
 * This is free software, placed under the terms of the
 * GNU General Public License, as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any
 * later version. Please see the file LICENSE-GPL for details.
 *
 * Web Page: http://mielke.cc/brltty/
 *
 * This software is maintained by Dave Mielke <dave@mielke.cc>.
 */

#include "prologue.h"

#include <errno.h>

#include "log.h"
#include "brldefs.h"

#include "scr_driver.h"
#include "system_java.h"

static JNIEnv *env = NULL;
static jclass screenDriverClass = NULL;
static jclass inputServiceClass = NULL;
static jclass lockUtilitiesClass = NULL;

static jint screenNumber;
static jint screenColumns;
static jint screenRows;
static jint cursorColumn;
static jint cursorRow;
static jint selectedFrom;
static jint selectedTo;
static jint selectedLeft;
static jint selectedTop;
static jint selectedRight;
static jint selectedBottom;

static const char *problemText = NULL;

static int
findScreenDriverClass (void) {
  return findJavaClass(env, &screenDriverClass, "org/a11y/brltty/android/ScreenDriver");
}

static int
findInputServiceClass (void) {
  return findJavaClass(env, &inputServiceClass, "org/a11y/brltty/android/InputService");
}

static int
findLockUtilitiesClass (void) {
  return findJavaClass(env, &lockUtilitiesClass, "org/a11y/brltty/android/LockUtilities");
}

JNIEXPORT void JNICALL
Java_org_a11y_brltty_android_ScreenDriver_exportScreenProperties (
  JNIEnv *env, jobject this,
  jint number,
  jint columns, jint rows,
  jint column, jint row,
  jint from, jint to,
  jint left, jint top,
  int right, int bottom
) {
  screenNumber = number;
  screenColumns = columns;
  screenRows = rows;
  cursorColumn = column;
  cursorRow = row;
  selectedFrom = from;
  selectedTo = to;
  selectedLeft = left;
  selectedTop = top;
  selectedRight = right;
  selectedBottom = bottom;
}

static void
describe_AndroidScreen (ScreenDescription *description) {
  if (findScreenDriverClass()) {
    static jmethodID method = 0;

    if (findJavaStaticMethod(env, &method, screenDriverClass, "refreshScreen",
                             JAVA_SIG_METHOD(JAVA_SIG_BOOLEAN,
                                            ))) {
      jboolean result = (*env)->CallStaticBooleanMethod(env, screenDriverClass, method);

      if (clearJavaException(env, 1)) {
        description->unreadable = "java exception";
      } else if (result == JNI_FALSE) {
        description->unreadable = "device locked";
      } else {
        description->cols = screenColumns;
        description->rows = screenRows;
        description->posx = cursorColumn;
        description->posy = cursorRow;
        description->number = screenNumber;
        description->unreadable = NULL;
      }
    } else {
      description->unreadable = "method not found";
    }
  } else {
    description->unreadable = "class not found";
  }

  if ((problemText = description->unreadable)) {
    description->cols = strlen(problemText);
    description->rows = 1;
    description->posx = 0;
    description->posy = 0;
    description->number = 0;
  }
}

static int
getRowCharacters (ScreenCharacter *characters, jint rowNumber, jint columnNumber, jint columnCount) {
  if (findScreenDriverClass()) {
    static jmethodID method = 0;

    if (findJavaStaticMethod(env, &method, screenDriverClass, "getRowText",
                             JAVA_SIG_METHOD(JAVA_SIG_VOID, 
                                             JAVA_SIG_ARRAY(JAVA_SIG_CHAR) // textBuffer
                                             JAVA_SIG_INT // rowNumber
                                             JAVA_SIG_INT // columnNumber
                                            ))) {
      jcharArray textBuffer = (*env)->NewCharArray(env, columnCount);

      if (textBuffer) {
        (*env)->CallStaticVoidMethod(env, screenDriverClass, method, textBuffer, rowNumber, columnNumber);

        if (!clearJavaException(env, 1)) {
          jchar buffer[columnCount];

          (*env)->GetCharArrayRegion(env, textBuffer, 0, columnCount, buffer);
          (*env)->DeleteLocalRef(env, textBuffer);
          textBuffer = NULL;

          {
            const jchar *source = buffer;
            const jchar *end = source + columnCount;
            ScreenCharacter *target = characters;

            while (source < end) {
              target->text = *source++;
              target->attributes = SCR_COLOUR_DEFAULT;
              target += 1;
            }
          }

          if ((rowNumber >= selectedTop) && (rowNumber < selectedBottom)) {
            int from = MAX(selectedLeft, columnNumber);
            int to = MIN(selectedRight, columnNumber+columnCount);

            if (rowNumber == selectedTop) from += selectedFrom - selectedLeft;
            if (rowNumber == (selectedBottom - 1)) to -= selectedRight - selectedTo - 1;

            if (from < to) {
              ScreenCharacter *target = characters + (from - columnNumber);
              const ScreenCharacter *end = target + (to - from);

              while (target < end) {
                target->attributes = SCR_COLOUR_FG_BLACK | SCR_COLOUR_BG_LIGHT_GREY;
                target += 1;
              }
            }
          }

          return 1;
        }
      } else {
        logMallocError();
        clearJavaException(env, 0);
      }
    }
  }

  return 0;
}

static int
readCharacters_AndroidScreen (const ScreenBox *box, ScreenCharacter *buffer) {
  if (validateScreenBox(box, screenColumns, screenRows)) {
    if (problemText) {
      setScreenMessage(box, buffer, problemText);
    } else {
      int rowIndex;

      for (rowIndex=0; rowIndex<box->height; rowIndex+=1) {
        if (!getRowCharacters(&buffer[rowIndex * box->width], (rowIndex + box->top), box->left, box->width)) return 0;
      }
    }

    return 1;
  }

  return 0;
}

static int
resetLockTimer (void) {
  if (findLockUtilitiesClass()) {
    static jmethodID method = 0;

    if (findJavaStaticMethod(env, &method, lockUtilitiesClass, "resetTimer",
                             JAVA_SIG_METHOD(JAVA_SIG_VOID,
                                            ))) {
      (*env)->CallStaticVoidMethod(env, lockUtilitiesClass, method);
      if (!clearJavaException(env, 1)) return 1;
      errno = EIO;
    }
  }

  return 0;
}

static int
executeCommand_AndroidScreen (int *command) {
  resetLockTimer();
  return 0;
}

static int
routeCursor_AndroidScreen (int column, int row, int screen) {
  if (findScreenDriverClass()) {
    static jmethodID method = 0;

    if (findJavaStaticMethod(env, &method, screenDriverClass, "routeCursor",
                             JAVA_SIG_METHOD(JAVA_SIG_BOOLEAN,
                                             JAVA_SIG_INT // column
                                             JAVA_SIG_INT // row
                                            ))) {
      jboolean result = (*env)->CallStaticBooleanMethod(env, screenDriverClass, method, column, row);

      if (!clearJavaException(env, 1)) {
        if (result != JNI_FALSE) {
          return 1;
        }
      }
    }
  }

  return 0;
}

static int
insertKey_AndroidScreen (ScreenKey key) {
  if (findInputServiceClass()) {
    wchar_t character = key & SCR_KEY_CHAR_MASK;

    logMessage(LOG_DEBUG, "insert key: %04X", key);
    setKeyModifiers(&key, 0);

    if (!isSpecialKey(key)) {
      static jmethodID method = 0;

      if (findJavaStaticMethod(env, &method, inputServiceClass, "inputCharacter",
                               JAVA_SIG_METHOD(JAVA_SIG_BOOLEAN,
                                               JAVA_SIG_CHAR // character
                                              ))) {
        jboolean result = (*env)->CallStaticBooleanMethod(env, inputServiceClass, method, character);

        if (!clearJavaException(env, 1)) {
          if (result != JNI_FALSE) {
            return 1;
          }
        }
      }
    } else if (character < SCR_KEY_FUNCTION) {
#define KEY(key,method) [key] = method
      static const char *const methodNames[SCR_KEY_FUNCTION] = {
        KEY(SCR_KEY_ENTER, "inputKeyEnter"),
        KEY(SCR_KEY_TAB, "inputKeyTab"),
        KEY(SCR_KEY_BACKSPACE, "inputKeyBackspace"),
        KEY(SCR_KEY_ESCAPE, "inputKeyEscape"),
        KEY(SCR_KEY_CURSOR_LEFT, "inputKeyCursorLeft"),
        KEY(SCR_KEY_CURSOR_RIGHT, "inputKeyCursorRight"),
        KEY(SCR_KEY_CURSOR_UP, "inputKeyCursorUp"),
        KEY(SCR_KEY_CURSOR_DOWN, "inputKeyCursorDown"),
        KEY(SCR_KEY_PAGE_UP, "inputKeyPageUp"),
        KEY(SCR_KEY_PAGE_DOWN, "inputKeyPageDown"),
        KEY(SCR_KEY_HOME, "inputKeyHome"),
        KEY(SCR_KEY_END, "inputKeyEnd"),
        KEY(SCR_KEY_INSERT, "inputKeyInsert"),
        KEY(SCR_KEY_DELETE, "inputKeyDelete"),
      };
      const char *methodName = methodNames[character];
#undef KEY

      static jmethodID methodIdentifiers[SCR_KEY_FUNCTION];
      jmethodID *methodIdentifier = &methodIdentifiers[character];

      if (findJavaStaticMethod(env, methodIdentifier, inputServiceClass, methodName,
                               JAVA_SIG_METHOD(JAVA_SIG_BOOLEAN,
                                              ))) {
        jboolean result = (*env)->CallStaticBooleanMethod(env, inputServiceClass, *methodIdentifier);

        if (!clearJavaException(env, 1)) {
          if (result != JNI_FALSE) {
            return 1;
          }
        }
      }
    } else {
      static jmethodID method = 0;

      if (findJavaStaticMethod(env, &method, inputServiceClass, "inputKeyFunction",
                               JAVA_SIG_METHOD(JAVA_SIG_BOOLEAN,
                                               JAVA_SIG_INT // key
                                              ))) {
        jboolean result = (*env)->CallStaticBooleanMethod(env, inputServiceClass, method, character-SCR_KEY_FUNCTION);

        if (!clearJavaException(env, 1)) {
          if (result != JNI_FALSE) {
            return 1;
          }
        }
      }
    }
  }

  logMessage(LOG_WARNING, "unsuported key: %04X", key);
  return 0;
}

static void
scr_initialize (MainScreen *main) {
  initializeRealScreen(main);
  main->base.describe = describe_AndroidScreen;
  main->base.readCharacters = readCharacters_AndroidScreen;
  main->base.executeCommand = executeCommand_AndroidScreen;
  main->base.routeCursor = routeCursor_AndroidScreen;
  main->base.insertKey = insertKey_AndroidScreen;
  env = getJavaNativeInterface();
}
