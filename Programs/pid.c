/*
 * BRLTTY - A background process providing access to the console screen (when in
 *          text mode) for a blind person using a refreshable braille display.
 *
 * Copyright (C) 1995-2010 by The BRLTTY Developers.
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

#include "pid.h"

#if defined(__MINGW32__)
ProcessIdentifier
getProcessIdentifier (void) {
  return GetCurrentProcessId();
}

int
testProcessIdentifier (ProcessIdentifier pid) {
  HANDLE handle = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);
  if (!handle) return 0;
  CloseHandle(handle);
  return 1;
}

#elif defined(__MSDOS__)
ProcessIdentifier
getProcessIdentifier (void) {
  return DOS_PROCESS_ID;
}

int
testProcessIdentifier (ProcessIdentifier pid) {
  return pid == DOS_PROCESS_ID;
}

#else /* Unix */
#include <signal.h>

ProcessIdentifier
getProcessIdentifier (void) {
  return getpid();
}

int
testProcessIdentifier (ProcessIdentifier pid) {
  return kill(pid, 0) != -1;
}

#endif /* pid support */
