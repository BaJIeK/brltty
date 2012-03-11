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

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "scr.h"
#include "tunes.h"
#include "clipboard.h"

/* Global state variables */
wchar_t *cpbBuffer = NULL;
size_t cpbLength = 0;

static int beginColumn = 0;
static int beginRow = 0;
static int beginOffset = -1;

static wchar_t *
mallocWchars (size_t count) {
  return malloc(count * sizeof(wchar_t));
}

static wchar_t *
copy (size_t *length, int fromColumn, int fromRow, int toColumn, int toRow) {
  wchar_t *newBuffer = NULL;
  int columns = toColumn - fromColumn + 1;
  int rows = toRow - fromRow + 1;

  if ((columns >= 1) && (rows >= 1) && (beginOffset >= 0)) {
    wchar_t *fromBuffer = mallocWchars(rows * columns);
    if (fromBuffer) {
      wchar_t *toBuffer = mallocWchars(rows * (columns + 1));
      if (toBuffer) {
        if (readScreenText(fromColumn, fromRow, columns, rows, fromBuffer)) {
          wchar_t *fromAddress = fromBuffer;
          wchar_t *toAddress = toBuffer;
          int row;

          for (row=fromRow; row<=toRow; row+=1) {
            int column;

            for (column=fromColumn; column<=toColumn; column+=1) {
              wchar_t character = *fromAddress++;
              if (iswcntrl(character) || iswspace(character)) character = WC_C(' ');
              *toAddress++ = character;
            }

            if (row != toRow) *toAddress++ = WC_C('\r');
          }

          /* make a new permanent buffer of just the right size */
          {
            size_t newLength = toAddress - toBuffer;
            if ((newBuffer = mallocWchars(newLength))) {
              wmemcpy(newBuffer, toBuffer, (*length = newLength));
            }
          }
        }
        
        free(toBuffer);
      }

      free(fromBuffer);
    }
  }

  return newBuffer;
}

static int
append (wchar_t *buffer, size_t length) {
  if (cpbBuffer) {
    size_t newLength = beginOffset + length;
    wchar_t *newBuffer = mallocWchars(newLength);
    if (!newBuffer) return 0;

    wmemcpy(wmempcpy(newBuffer, cpbBuffer, beginOffset), buffer, length);

    free(buffer);
    free(cpbBuffer);

    cpbBuffer = newBuffer;
    cpbLength = newLength;
  } else {
    cpbBuffer = buffer;
    cpbLength = length;
  }

  playTune(&tune_copy_end);
  return 1;
}

void
cpbClear (void) {
  if (cpbBuffer) {
    free(cpbBuffer);
    cpbBuffer = NULL;
  }
  cpbLength = 0;
}

void
cpbStart (int column, int row) {
  cpbClear();
  cpbExtend(column, row);
}

void
cpbExtend (int column, int row) {
  beginColumn = column;
  beginRow = row;
  beginOffset = cpbLength;
  playTune(&tune_copy_begin);
}

int
cpbRectangularCopy (int column, int row) {
  size_t length;
  wchar_t *buffer = copy(&length, beginColumn, beginRow, column, row);

  if (buffer) {
    {
      const wchar_t *from = buffer;
      const wchar_t *end = from + length;
      wchar_t *to = buffer;
      int spaces = 0;

      while (from != end) {
        wchar_t character = *from++;

        switch (character) {
          case WC_C(' '):
            spaces += 1;
            continue;

          case WC_C('\r'):
            spaces = 0;

          default:
            break;
        }

        while (spaces) {
          *to++ = WC_C(' ');
          spaces -= 1;
        }

        *to++ = character;
      }

      length = to - buffer;
    }

    if (append(buffer, length)) return 1;
    free(buffer);
  }
  return 0;
}

int
cpbLinearCopy (int column, int row) {
  ScreenDescription screen;
  describeScreen(&screen);

  {
    int rightColumn = screen.cols - 1;
    size_t length;
    wchar_t *buffer = copy(&length, 0, beginRow, rightColumn, row);

    if (buffer) {
      if (column < rightColumn) {
        wchar_t *start = buffer + length;
        while (start != buffer) {
          if (*--start == WC_C('\r')) {
            start += 1;
            break;
          }
        }

        {
          int adjustment = (column + 1) - (buffer + length - start);
          if (adjustment < 0) length += adjustment;
        }
      }

      if (beginColumn) {
        wchar_t *start = wmemchr(buffer, WC_C('\r'), length);
        if (!start) start = buffer + length;
        if ((start - buffer) > beginColumn) start = buffer + beginColumn;
        if (start != buffer) wmemmove(buffer, start, (length -= start - buffer));
      }

      {
        const wchar_t *from = buffer;
        const wchar_t *end = from + length;
        wchar_t *to = buffer;
        int spaces = 0;
        int newlines = 0;

        while (from != end) {
          wchar_t character = *from++;

          switch (character) {
            case WC_C(' '):
              spaces += 1;
              continue;

            case WC_C('\r'):
              newlines += 1;
              continue;

            default:
              break;
          }

          if (newlines) {
            if ((newlines > 1) || (spaces > 0)) spaces = 1;
            newlines = 0;
          }

          while (spaces) {
            *to++ = WC_C(' ');
            spaces -= 1;
          }

          *to++ = character;
        }

        length = to - buffer;
      }

      if (append(buffer, length)) return 1;
      free(buffer);
    }
  }

  return 0;
}

int
cpbPaste (void) {
  if (!cpbLength) return 0;

  {
    int i;
    for (i=0; i<cpbLength; ++i)
      if (!insertScreenKey(cpbBuffer[i]))
        return 0;
  }

  return 1;
}