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

void *
loadSharedObject (const char *path) {
#ifdef HAVE_FUNC_DLOPEN 
  void *object = dlopen(path, SHARED_OBJECT_LOAD_FLAGS);
  if (object) return object;
  LogPrint(LOG_ERR, "%s", dlerror());
#endif /* HAVE_FUNC_DLOPEN */
  return NULL;
}

void 
unloadSharedObject (void *object) {
#ifdef HAVE_FUNC_DLOPEN 
  dlclose(object);
#endif /* HAVE_FUNC_DLOPEN */
}

int 
findSharedSymbol (void *object, const char *symbol, const void **address) {
#ifdef HAVE_FUNC_DLOPEN 
  const char *error;
  *address = dlsym(object, symbol);
  if (!(error = dlerror())) return 1;
  LogPrint(LOG_ERR, "%s", error);
#endif /* HAVE_FUNC_DLOPEN */
  return 0;
}
