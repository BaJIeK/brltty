/*
 * BRLTTY - A background process providing access to the Linux console (when in
 *          text mode) for a blind person using a refreshable braille display.
 *
 * Copyright (C) 1995-2004 by The BRLTTY Team. All rights reserved.
 *
 * BRLTTY comes with ABSOLUTELY NO WARRANTY.
 *
 * This is free software, placed under the terms of the
 * GNU Lesser General Public License, as published by the Free Software
 * Foundation; either version 2.1 of the License,
 * or (at your option) any later version.
 * Please see the file COPYING-API for details.
 *
 * Web Page: http://mielke.cc/brltty/
 *
 * This software is maintained by Dave Mielke <dave@mielke.cc>.
 */

#ifndef _BRLDEFS_H
#define _BRLDEFS_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Argument for brl_readCommand() */
typedef enum {
  BRL_CTX_SCREEN,
  BRL_CTX_HELP,
  BRL_CTX_STATUS,
  BRL_CTX_PREFS,
  BRL_CTX_MESSAGE
} BRL_DriverCommandContext;

/* The following command codes are return values for brl_readCommand().
 * The BRL_CMD_* codes are guaranteed to be between 1 and 255
 * inclusive, with the exception of BRL_CMD_NOOP = 0.
 *
 * brl_readCommand() should return EOF if there are no keys to return,  If,
 * however, if it has masked out the key for internal use, it may return
 * BRL_CMD_NOOP - in which case it will be called again immediately, rather
 * than waiting for the next cycle.  This can save internal nesting ...
 */

/*
 * Please comment all BRL_CMD_* definitions. They are
 * used during automatic help file generation.
 */
typedef enum {
  /* special commands which must be first and remain in order */
  BRL_CMD_NOOP = 0 /* do nothing */,

  /* vertical motion */
  BRL_CMD_LNUP /* go up one line */,
  BRL_CMD_LNDN /* go down one line */,
  BRL_CMD_WINUP /* go up several lines */,
  BRL_CMD_WINDN /* go down several lines */,
  BRL_CMD_PRDIFLN /* go up to nearest line with different content */,
  BRL_CMD_NXDIFLN /* go down to nearest line with different content */,
  BRL_CMD_ATTRUP /* go up to nearest line with different highlighting */,
  BRL_CMD_ATTRDN /* go down to nearest line with different highlighting */,
  BRL_CMD_TOP /* go to top line */,
  BRL_CMD_BOT /* go to bottom line */,
  BRL_CMD_TOP_LEFT /* go to top-left corner */,
  BRL_CMD_BOT_LEFT /* go to bottom-left corner */,
  BRL_CMD_PRPGRPH /* go up to last line of previous paragraph */,
  BRL_CMD_NXPGRPH /* go down to first line of next paragraph */,
  BRL_CMD_PRPROMPT /* go up to previous command prompt */,
  BRL_CMD_NXPROMPT /* go down to next command prompt */,
  BRL_CMD_PRSEARCH /* search backward for content of cut buffer */,
  BRL_CMD_NXSEARCH /* search forward for content of cut buffer */,
  
  /* horizontal motion */
  BRL_CMD_CHRLT /* go left one character */,
  BRL_CMD_CHRRT /* go right one character */,
  BRL_CMD_HWINLT /* go left half a window */,
  BRL_CMD_HWINRT /* go right half a window */,
  BRL_CMD_FWINLT /* go left one window */,
  BRL_CMD_FWINRT /* go right one window */,
  BRL_CMD_FWINLTSKIP /* go left to nearest non-blank window */,
  BRL_CMD_FWINRTSKIP /* go right to nearest non-blank window */,
  BRL_CMD_LNBEG /* go to beginning of line */,
  BRL_CMD_LNEND /* go to end of line */,
  
  /* implicit motion */
  BRL_CMD_HOME /* go to cursor */,
  BRL_CMD_BACK /* go back (undo unexpected cursor tracking motion) */,
  BRL_CMD_RETURN /* go back (after cursor tracking) or to cursor (cursor not in window) */,
  
  /* feature activation and deactivation */
  BRL_CMD_FREEZE /* toggle screen mode frozen/live */,
  BRL_CMD_DISPMD /* toggle display mode attributes/text */,
  BRL_CMD_SIXDOTS /* toggle text style 6-dot/8-dot */,
  BRL_CMD_SLIDEWIN /* toggle sliding window on/off */,
  BRL_CMD_SKPIDLNS /* toggle skipping of lines with identical content on/off */,
  BRL_CMD_SKPBLNKWINS /* toggle skipping of blank windows on/off */,
  BRL_CMD_CSRVIS /* toggle cursor visibility on/off */,
  BRL_CMD_CSRHIDE /* toggle hidden cursor on/off */,
  BRL_CMD_CSRTRK /* toggle cursor tracking on/off */,
  BRL_CMD_CSRSIZE /* toggle cursor style block/underline */,
  BRL_CMD_CSRBLINK /* toggle cursor blinking on/off */,
  BRL_CMD_ATTRVIS /* toggle attribute underlining on/off */,
  BRL_CMD_ATTRBLINK /* toggle attribute blinking on/off */,
  BRL_CMD_CAPBLINK /* toggle capital letter blinking on/off */,
  BRL_CMD_TUNES /* toggle alert tunes on/off */,
  BRL_CMD_AUTOREPEAT /* toggle autorepeat on/off */,
  BRL_CMD_AUTOSPEAK /* toggle autospeak on/off */,
 
  /* mode selection */
  BRL_CMD_HELP /* enter/leave help display */,
  BRL_CMD_INFO /* enter/leave status display */,
  BRL_CMD_LEARN /* enter/leave command learn mode */,
  
  /* preference setting */
  BRL_CMD_PREFMENU /* enter/leave preferences menu */,
  BRL_CMD_PREFSAVE /* save current preferences */,
  BRL_CMD_PREFLOAD /* restore saved preferences */,
  
  /* menu navigation */
  BRL_CMD_MENU_FIRST_ITEM /* go to first item in menu */,
  BRL_CMD_MENU_LAST_ITEM /* go to last item in menu */,
  BRL_CMD_MENU_PREV_ITEM /* go to previous item in menu */,
  BRL_CMD_MENU_NEXT_ITEM /* go to next item in menu */,
  BRL_CMD_MENU_PREV_SETTING /* change current item in menu to previous choice */,
  BRL_CMD_MENU_NEXT_SETTING /* change current item in menu to next choice */,
 
  /* speech controls */
  BRL_CMD_MUTE /* stop speaking immediately */,
  BRL_CMD_SPKHOME /* go to current (most recent) speech position */,
  BRL_CMD_SAY_LINE /* speak current line */,
  BRL_CMD_SAY_ABOVE /* speak from top of screen through current line */,
  BRL_CMD_SAY_BELOW /* speak from current line through bottom of screen */,
  BRL_CMD_SAY_SLOWER /* decrease speech rate */,
  BRL_CMD_SAY_FASTER /* increase speech rate */,
  BRL_CMD_SAY_SOFTER /* decrease speech volume */,
  BRL_CMD_SAY_LOUDER /* increase speech volume */,
  
  /* virtual terminal switching */
  BRL_CMD_SWITCHVT_PREV /* switch to previous virtual terminal */,
  BRL_CMD_SWITCHVT_NEXT /* switch to next virtual terminal */,
  
  /* miscellaneous */
  BRL_CMD_CSRJMP_VERT /* bring cursor to line (no horizontal motion) */,
  BRL_CMD_PASTE /* insert cut buffer at cursor */,
  BRL_CMD_RESTARTBRL /* reinitialize braille driver */,
  BRL_CMD_RESTARTSPEECH /* reinitialize speech driver */,
  
  BRL_driverCommandCount /* must be last */
} BRL_DriverCommand;

#define BRL_MSK_ARG 0XFF
#define BRL_MSK_BLK 0XFF00
#define BRL_MSK_FLG 0XFF0000
#define BRL_MSK_CMD (BRL_MSK_BLK | BRL_MSK_ARG)
  
/* For explicitly setting toggles on/off. */
#define BRL_FLG_TOGGLE_ON   0x010000
#define BRL_FLG_TOGGLE_OFF  0x020000
#define BRL_FLG_TOGGLE_MASK (BRL_FLG_TOGGLE_ON | BRL_FLG_TOGGLE_OFF)

#define BRL_FLG_REPEAT_INITIAL 0x800000
#define BRL_FLG_REPEAT_DELAY   0x400000
#define BRL_FLG_REPEAT_MASK    (BRL_FLG_REPEAT_INITIAL | BRL_FLG_REPEAT_DELAY)
  
/* cursor routing keys block offset values */
/*
 * Please comment all BRL_BLK_* definitions. They are
 * used during automatic help file generation.
 */
#define BRL_BLK_ROUTE     0X100 /* bring cursor to character */
#define BRL_BLK_CUTBEGIN  0X200 /* start new cut buffer at character */
#define BRL_BLK_CUTAPPEND 0X300 /* append to existing cut buffer from character */
#define BRL_BLK_CUTRECT   0X400 /* rectangular cut to character */
#define BRL_BLK_CUTLINE   0X500 /* linear cut to character */
#define BRL_BLK_SWITCHVT  0X600 /* switch to virtual terminal */
#define BRL_BLK_PRINDENT  0X700 /* go up to nearest line without greater indent */
#define BRL_BLK_NXINDENT  0X800 /* go down to nearest line without greater indent */
#define BRL_BLK_DESCCHAR  0X900 /* describe character */
#define BRL_BLK_SETLEFT   0XA00 /* position left end of window at character */
#define BRL_BLK_SETMARK   0XB00 /* remember current window position */
#define BRL_BLK_GOTOMARK  0XC00 /* go to remembered window position */

/* For entering a special key. */
#define BRL_BLK_PASSKEY 0X2000
typedef enum {
  BRL_KEY_ENTER,
  BRL_KEY_TAB,
  BRL_KEY_BACKSPACE,
  BRL_KEY_ESCAPE,
  BRL_KEY_CURSOR_LEFT,
  BRL_KEY_CURSOR_RIGHT,
  BRL_KEY_CURSOR_UP,
  BRL_KEY_CURSOR_DOWN,
  BRL_KEY_PAGE_UP,
  BRL_KEY_PAGE_DOWN,
  BRL_KEY_HOME,
  BRL_KEY_END,
  BRL_KEY_INSERT,
  BRL_KEY_DELETE,
  BRL_KEY_FUNCTION
} BRL_Key;

#define BRL_BLK_PASSCHAR 0X2100 /* input character by value */
#define BRL_BLK_PASSDOTS 0X2200 /* input character as braille dots */

/* For modifying a character to be typed. */
#define BRL_FLG_CHAR_CONTROL 0X010000
#define BRL_FLG_CHAR_META    0X020000
#define BRL_FLG_CHAR_UPPER   0X040000
#define BRL_FLG_CHAR_SHIFT   0X080000

#define BRL_BLK_PASSAT2 0X2300 /* input AT set 2 keyboard scan code */

/*
 * Please comment all BRL_GSC_* definitions. They are
 * used during automatic help file generation.
 */
#define BRL_STATUS_CELLS_GENERIC 0XFF /* must be in BRL_firstStatusCell */
typedef enum {
  BRL_firstStatusCell = 0,

  /* numbers */
  BRL_GSC_BRLCOL /* screen column where left of braille window is */,
  BRL_GSC_BRLROW /* screen row where top of braille window is */,
  BRL_GSC_CSRCOL /* screen column where cursor is */,
  BRL_GSC_CSRROW /* screen row where cursor is */,
  BRL_GSC_SCRNUM /* virtual screen number */,

  /* flags */
  BRL_GSC_FREEZE /* frozen screen */,
  BRL_GSC_DISPMD /* attributes display */,
  BRL_GSC_SIXDOTS /* six-dot braille */,
  BRL_GSC_SLIDEWIN /* sliding window */,
  BRL_GSC_SKPIDLNS /* skip identical lines */,
  BRL_GSC_SKPBLNKWINS /* skip blank windows */,
  BRL_GSC_CSRVIS /* visible cursor */,
  BRL_GSC_CSRHIDE /* hidden cursor */,
  BRL_GSC_CSRTRK /* cursor tracking */,
  BRL_GSC_CSRSIZE /* block cursor */,
  BRL_GSC_CSRBLINK /* blinking cursor */,
  BRL_GSC_ATTRVIS /* visible attributes underline */,
  BRL_GSC_ATTRBLINK /* blinking attributes underline */,
  BRL_GSC_CAPBLINK /* blinking capital letters */,
  BRL_GSC_TUNES /* alert tunes */,
  BRL_GSC_HELP /* help mode */,
  BRL_GSC_INFO /* info mode */,
  BRL_GSC_AUTOREPEAT /* autorepeat */,
  BRL_GSC_AUTOSPEAK /* autospeak */,

  BRL_genericStatusCellCount
} BRL_GenericStatusCell;
#define BRL_MAX_STATUS_CELL_COUNT (MAX(22, BRL_genericStatusCellCount))

/* The bits for each braille dot.
 *
 * DotNumber  BitNumber  ActualBit
 *    1 4        0 1     0X01 0X02
 *    2 5        2 3     0X04 0X08
 *    3 6        4 5     0X10 0X20
 *    7 8        6 7     0X40 0X80
 *
 * This dot mapping was chosen for BRLTTY's internal dot representation
 * because it makes programming prettier and more efficient for things such
 * as underlining, cursor drawing, and vertical braille character shifting.
 *
 * Bx: x from dot number, value from actual bit.
 */
#define BRL_DOT1 0X01
#define BRL_DOT2 0X04
#define BRL_DOT3 0X10
#define BRL_DOT4 0X02
#define BRL_DOT5 0X08
#define BRL_DOT6 0X20
#define BRL_DOT7 0X40
#define BRL_DOT8 0X80

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _BRLDEFS_H */
