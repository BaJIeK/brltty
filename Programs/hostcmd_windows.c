/*
 * BRLTTY - A background process providing access to the console screen (when in
 *          text mode) for a blind person using a refreshable braille display.
 *
 * Copyright (C) 1995-2013 by The BRLTTY Developers.
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

#include "hostcmd_windows.h"
#include "hostcmd_internal.h"

int
isHostCommand (const char *path) {
  return 0;
}

void
subconstructHostCommandStream (HostCommandStream *hcs) {
}

void
subdestructHostCommandStream (HostCommandStream *hcs) {
}

int
prepareHostCommandStream (HostCommandStream *hcs) {
  return 1;
}

int
runCommand (
  int *result,
  const char *const *command,
  HostCommandStream *streams,
  int asynchronous
) {
  return 0;
}
