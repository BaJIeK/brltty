/*
 * BRLTTY - A background process providing access to the console screen (when in
 *          text mode) for a blind person using a refreshable braille display.
 *
 * Copyright (C) 1995-2005 by The BRLTTY Team. All rights reserved.
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

/* tbl2hex.c - filter to compile 256-byte table file into C code
 * $Id: tbl2hex.c,v 1.3 1996/09/24 01:04:25 nn201 Exp $
 */

#include "prologue.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "options.h"
#include "misc.h"
#include "brl.h"
#include "ctb.h"
#include "tbl.h"

static char *opt_dataDirectory;
static char *opt_contractionTable;
static char *opt_textTable;
static char *opt_outputWidth;

BEGIN_OPTION_TABLE
  {"contraction-table", "file", 'c', 0, 0,
   &opt_contractionTable, "en-us-g2.ctb",
   "Path to contraction table file."},

  {"text-table", "file", 't', 0, 0,
   &opt_textTable, TEXT_TABLE,
   "Text translation table."},

  {"output-width", "columns", 'w', 0, 0,
   &opt_outputWidth, "",
   "Maximum length of an output line."},

  {"data-directory", "file", 'D', 0, OPT_Hidden,
   &opt_dataDirectory, DATA_DIRECTORY,
   "Path to directory for configuration files."},
END_OPTION_TABLE

TranslationTable textTable;
TranslationTable untextTable;
void *contractionTable;

static int outputWidth;
static int outputExtend;
static unsigned char *outputBuffer;

typedef struct {
  unsigned char status;
} LineProcessingData;

static int
contractLine (char *line, void *data) {
  LineProcessingData *lpd = data;
  int lineLength = strlen(line);
  int offsets[lineLength];

  while (lineLength) {
    int inputCount = lineLength;
    int outputCount = outputWidth;

    if (!outputBuffer) {
      if (!(outputBuffer = malloc(outputWidth))) {
        LogError("output buffer allocation");
        lpd->status = 10;
        return 0;
      }
    }

    if (!contractText(contractionTable,
                      (unsigned char *)line, &inputCount,
                      outputBuffer, &outputCount,
                      offsets, -1)) {
      lpd->status = 11;
      return 0;
    }

    if ((inputCount < lineLength) && outputExtend) {
      free(outputBuffer);
      outputBuffer = NULL;
      outputWidth <<= 1;
    } else {
      {
        int index;
        for (index=0; index<outputCount; ++index)
          outputBuffer[index] = untextTable[outputBuffer[index]];
      }

      {
        FILE *output = stdout;
        fwrite(outputBuffer, 1, outputCount, output);
        if (!ferror(output)) fputc('\n', output);
        if (ferror(output)) {
          LogError("output");
          lpd->status = 12;
          return 0;
        }
      }

      line += inputCount;
      lineLength -= inputCount;
    }
  }

  return 1;
}

static int
contractFile (FILE *file) {
  LineProcessingData lpd;
  lpd.status = 0;
  return processLines(file, contractLine, &lpd)? lpd.status: 5;
}

int
main (int argc, char *argv[]) {
  int status = 3;

  processOptions(optionTable, optionCount,
                 "ctbtest", &argc, &argv,
                 NULL, NULL, NULL,
                 "contraction-table");

  if ((outputExtend = !*opt_outputWidth)) {
    outputWidth = 0X80;
  } else {
    static const int minimum = 1;
    if (!validateInteger(&outputWidth, "output width", opt_outputWidth, &minimum, NULL)) exit(2);
  }
  outputBuffer = NULL;

  {
    char *contractionTablePath;

    if ((contractionTablePath = makePath(opt_dataDirectory, opt_contractionTable))) {
      if ((contractionTable = compileContractionTable(contractionTablePath))) {
        char *textTablePath;

        if ((textTablePath = makePath(opt_dataDirectory, opt_textTable))) {
          if (loadTranslationTable(textTablePath, NULL, textTable, 0)) {
            reverseTranslationTable(textTable, untextTable);

            if (argc) {
              do {
                char *path = *argv;
                if (strcmp(path, "-") == 0) {
                  status = contractFile(stdin);
                } else {
                  FILE *file = fopen(path, "r");
                  if (file) {
                    status = contractFile(file);
                  } else{
                    LogPrint(LOG_ERR, "cannot open input file: %s: %s",
                             path, strerror(errno));
                    status = 6;
                  }
                }
              } while ((status == 0) && (++argv, --argc));
            } else {
              status = contractFile(stdin);
            }
          } else {
            status = 4;
          }
          free(textTablePath);
        } else {
          status = 4;
        }
        destroyContractionTable(contractionTable);
      } else {
        status = 3;
      }
      free(contractionTablePath);
    } else {
      status = 3;
    }
  }

  if (outputBuffer) free(outputBuffer);
  return status;
}
