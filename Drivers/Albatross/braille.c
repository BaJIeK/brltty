/*
 * BRLTTY - A background process providing access to the Linux console (when in
 *          text mode) for a blind person using a refreshable braille display.
 *
 * Copyright (C) 1995-2004 by The BRLTTY Team. All rights reserved.
 *
 * BRLTTY comes with ABSOLUTELY NO WARRANTY.
 *
 * This is free software, placed under the terms of the
 * GNU General Public License, as published by the Free Software
 * Foundation.  Please see the file COPYING for details.
 *
 * Web Page: http://mielke.cc/brltty/
 *
 * This software is maintained by Dave Mielke <dave@mielke.cc>.
 */

/* Albatross/braille.c - Braille display library
 * Tivomatic's Albatross series
 * Author: Dave Mielke <dave@mielke.cc>
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "Programs/misc.h"

#include "Programs/brl_driver.h"
#include "braille.h"

static int fileDescriptor = -1;
static struct termios oldSettings;
static struct termios newSettings;

static TranslationTable outputTable;
static int cellCount;
static unsigned char cellContent[80];

static int
readByte (unsigned char *byte) {
  int received = read(fileDescriptor, byte, 1);
  if (received == -1) LogError("Albatross read");
  return received == 1;
}

static int
awaitByte (unsigned char *byte) {
  if (awaitInput(fileDescriptor, 4000))
    if (readByte(byte))
      return 1;
  return 0;
}

static int
writeBytes (unsigned char *bytes, int count) {
  if (safe_write(fileDescriptor, bytes, count) != -1) return 1;
  LogError("Albatross write");
  return 0;
}

static int
acknowledgeDisplay (void) {
  unsigned char attributes;
  cellCount = 0;

  if (!awaitByte(&attributes)) return 0;
  {
    unsigned char acknowledgement[] = {0XFE, 0XFF, 0XFE, 0XFF};
    if (!writeBytes(acknowledgement, sizeof(acknowledgement))) return 0;
  }

  cellCount = (attributes & 0X80)? 80: 40;
  LogPrint(LOG_INFO, "Albatross detected: %d columns",
           baud2integer(cellCount));
  return 1;
}

static int
clearDisplay (void) {
  unsigned char bytes[] = {0XFA};
  int cleared = writeBytes(bytes, sizeof(bytes));
  if (cleared) memset(cellContent, 0, cellCount);
  return cleared;
}

static int
updateDisplay (unsigned char *cells) {
  unsigned char bytes[cellCount * 2 + 2];
  unsigned char *byte = bytes;
  int column;
  *byte++ = 0XFB;
  for (column=0; column<cellCount; ++column) {
    unsigned char cell;
    if (!cells) {
      cell = cellContent[column];
    } else if ((cell = outputTable[cells[column]]) != cellContent[column]) {
      cellContent[column] = cell;
    } else {
      continue;
    }
    *byte++ = column + 1;
    *byte++ = cell;
  }
  if ((byte - bytes) == 1) return 1;
  *byte++ = 0XFC;
  return writeBytes(bytes, byte-bytes);
}

static void
brl_identify (void) {
   LogPrint(LOG_NOTICE, "Albatross Driver");
   LogPrint(LOG_INFO, "   Copyright (C) 2004 by Dave Mielke <dave@mielke.cc>");
}

static int
brl_open (BrailleDisplay *brl, char **parameters, const char *device) {
  {
    static const DotsTable dots = {0X80, 0X40, 0X20, 0X10, 0X08, 0X04, 0X02, 0X01};
    makeOutputTable(&dots, &outputTable);
  }

  if (openSerialDevice(device, &fileDescriptor, &oldSettings)) {
    speed_t speedTable[] = {B9600, B19200, B0};
    const speed_t *speed = speedTable;

    memset(&newSettings, 0, sizeof(newSettings));
    newSettings.c_cflag = CS8 | CREAD;
    newSettings.c_iflag = IGNPAR;

    while (resetSerialDevice(fileDescriptor, &newSettings, *speed)) {
      unsigned char byte;
      while (awaitByte(&byte)) {
        if (byte == 0XFF) {
          if (acknowledgeDisplay()) {
            clearDisplay();
            brl->x = cellCount;
            brl->y = 1;
            return 1;
          }
        }
      }
      if (*++speed == B0) speed = speedTable;
    }

    tcsetattr(fileDescriptor, TCSANOW, &oldSettings);
    close(fileDescriptor);
    fileDescriptor = -1;
  }
  return 0;
}

static void
brl_close (BrailleDisplay *brl) {
  tcsetattr(fileDescriptor, TCSADRAIN, &oldSettings);
  close(fileDescriptor);
  fileDescriptor = -1;
}

static void
brl_writeWindow (BrailleDisplay *brl) {
  if (cellCount) {
    updateDisplay(brl->buffer);
  }
}

static void
brl_writeStatus (BrailleDisplay *brl, const unsigned char *status) {
  if (cellCount) {
  }
}

static int
brl_readCommand (BrailleDisplay *brl, DriverCommandContext cmds) {
  unsigned char byte;
  while (readByte(&byte)) {
    if (byte == 0XFF) {
      if (acknowledgeDisplay())  {
        updateDisplay(NULL);
        brl->resizeRequired = 1;
      }
      continue;
    }
    if (!cellCount) continue;

    switch (byte) {
      default:
        if ((byte >= 2) && (byte <= 41)) return CR_ROUTE + (byte - 2);
        if ((byte >= 111) && (byte <= 150)) return CR_ROUTE + (byte - 71);
        break;

      case 0XFB:
        updateDisplay(NULL);
        continue;

      case  83: /* top left first lower */
      case 193: /* top right first lower */
        return CMD_LEARN;

      case  84: /* top left first upper */
      case 194: /* top right first upper */
        return CMD_HELP;

      case  85: /* top left third upper */
      case 195: /* top right third upper */
        return CMD_PRDIFLN;

      case  86: /* top left third lower */
      case 196: /* top right third lower */
        return CMD_NXDIFLN;

      case  87: /* top left second */
      case 198: /* top right second */
        return CMD_CSRJMP_VERT;

      case  88: /* top left fourth */
      case 197: /* top right fourth */
        return CMD_BACK;

      case  89: /* top left fifth upper */
      case 199: /* top right fifth upper */
        return CMD_PREFMENU;

      case  90: /* top left fifth lower */
      case 200: /* top right fifth lower */
        return CMD_INFO;

      /* home */
      case  91: /* front left first upper */
      case 201: /* front right first upper */
        return CMD_TOP_LEFT;

      /* end */
      case  92: /* front left first lower */
      case 202: /* front right first lower */
        return CMD_BOT_LEFT;

      /* cursor */
      case  93: /* front left second upper */
      case 203: /* front right second upper */
        return CMD_CSRTRK;

      /* extra cursor */
      case  94: /* front left second lower */
      case 204: /* front right second lower */
        return CMD_HOME;

      /* up */
      case  95: /* front left third upper */
      case 205: /* front right third upper */
        return CMD_LNUP;

      /* down */
      case  96: /* front left third lower */
      case 206: /* front right third lower */
        return CMD_LNDN;

      /* left */
      case  97: /* front left fourth */
        return CMD_FWINLT;

      /* right */
      case 207: /* front right fourth */
        return CMD_FWINRT;
    }

    LogPrint(LOG_WARNING, "Unexpected byte: %02X", byte);
  }

  return EOF;
}
