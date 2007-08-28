/*
 * BRLTTY - A background process providing access to the console screen (when in
 *          text mode) for a blind person using a refreshable braille display.
 *
 * Copyright (C) 1995-2007 by The BRLTTY Developers.
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

#include "prologue.h"

#include "misc.h"
#include "system.h"
#include "notes.h"

static int beeperEnabled = 0;

static int
beeperConstruct (int errorLevel) {
  if (!beeperEnabled) {
    if (!canBeep()) {
      LogPrint(LOG_DEBUG, "beeper not available");
      return 0;
    }

    beeperEnabled = 1;
    LogPrint(LOG_DEBUG, "beeper enabled");
  }

  return 1;
}

static int
beeperPlay (int note, int duration) {
  if (beeperEnabled) {
    LogPrint(LOG_DEBUG, "tone: msec=%d note=%d",
             duration, note);

    if (!note) {
      accurateDelay(duration);
      return 1;
    }

    if (asynchronousBeep((int)noteFrequencies[note], duration*4)) {
      accurateDelay(duration);
      stopBeep();
      return 1;
    }

    if (startBeep((int)noteFrequencies[note])) {
      accurateDelay(duration);
      stopBeep();
      return 1;
    }

    if (synchronousBeep((int)noteFrequencies[note], duration)) return 1;
  }

  return 0;
}

static int
beeperFlush (void) {
  return beeperEnabled;
}

static void
beeperDestruct (void) {
  if (beeperEnabled) {
    beeperEnabled = 0;
    endBeep();
    LogPrint(LOG_DEBUG, "beeper disabled");
  }
}

const NoteGenerator beeperNoteGenerator = {
  beeperConstruct,
  beeperPlay,
  beeperFlush,
  beeperDestruct
};
