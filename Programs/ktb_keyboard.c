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

#include "ktb_keyboard.h"

BEGIN_KEY_NAME_TABLE(keyboard)
  KBD_NAME_ENTRY(LETTER, A, "A"),
  KBD_NAME_ENTRY(LETTER, A, "LETTER_A"),

  KBD_NAME_ENTRY(LETTER, B, "B"),
  KBD_NAME_ENTRY(LETTER, B, "LETTER_B"),

  KBD_NAME_ENTRY(LETTER, C, "C"),
  KBD_NAME_ENTRY(LETTER, C, "LETTER_C"),

  KBD_NAME_ENTRY(LETTER, D, "D"),
  KBD_NAME_ENTRY(LETTER, D, "LETTER_D"),

  KBD_NAME_ENTRY(LETTER, E, "E"),
  KBD_NAME_ENTRY(LETTER, E, "LETTER_E"),

  KBD_NAME_ENTRY(LETTER, F, "F"),
  KBD_NAME_ENTRY(LETTER, F, "LETTER_F"),

  KBD_NAME_ENTRY(LETTER, G, "G"),
  KBD_NAME_ENTRY(LETTER, G, "LETTER_G"),

  KBD_NAME_ENTRY(LETTER, H, "H"),
  KBD_NAME_ENTRY(LETTER, H, "LETTER_H"),

  KBD_NAME_ENTRY(LETTER, I, "I"),
  KBD_NAME_ENTRY(LETTER, I, "LETTER_I"),

  KBD_NAME_ENTRY(LETTER, J, "J"),
  KBD_NAME_ENTRY(LETTER, J, "LETTER_J"),

  KBD_NAME_ENTRY(LETTER, K, "K"),
  KBD_NAME_ENTRY(LETTER, K, "LETTER_K"),

  KBD_NAME_ENTRY(LETTER, L, "L"),
  KBD_NAME_ENTRY(LETTER, L, "LETTER_L"),

  KBD_NAME_ENTRY(LETTER, M, "M"),
  KBD_NAME_ENTRY(LETTER, M, "LETTER_M"),

  KBD_NAME_ENTRY(LETTER, N, "N"),
  KBD_NAME_ENTRY(LETTER, N, "LETTER_N"),

  KBD_NAME_ENTRY(LETTER, O, "O"),
  KBD_NAME_ENTRY(LETTER, O, "LETTER_O"),

  KBD_NAME_ENTRY(LETTER, P, "P"),
  KBD_NAME_ENTRY(LETTER, P, "LETTER_P"),

  KBD_NAME_ENTRY(LETTER, Q, "Q"),
  KBD_NAME_ENTRY(LETTER, Q, "LETTER_Q"),

  KBD_NAME_ENTRY(LETTER, R, "R"),
  KBD_NAME_ENTRY(LETTER, R, "LETTER_R"),

  KBD_NAME_ENTRY(LETTER, S, "S"),
  KBD_NAME_ENTRY(LETTER, S, "LETTER_S"),

  KBD_NAME_ENTRY(LETTER, T, "T"),
  KBD_NAME_ENTRY(LETTER, T, "LETTER_T"),

  KBD_NAME_ENTRY(LETTER, U, "U"),
  KBD_NAME_ENTRY(LETTER, U, "LETTER_U"),

  KBD_NAME_ENTRY(LETTER, V, "V"),
  KBD_NAME_ENTRY(LETTER, V, "LETTER_V"),

  KBD_NAME_ENTRY(LETTER, W, "W"),
  KBD_NAME_ENTRY(LETTER, W, "LETTER_W"),

  KBD_NAME_ENTRY(LETTER, X, "X"),
  KBD_NAME_ENTRY(LETTER, X, "LETTER_X"),

  KBD_NAME_ENTRY(LETTER, Y, "Y"),
  KBD_NAME_ENTRY(LETTER, Y, "LETTER_Y"),

  KBD_NAME_ENTRY(LETTER, Z, "Z"),
  KBD_NAME_ENTRY(LETTER, Z, "LETTER_Z"),

  KBD_NAME_ENTRY(NUMBER, Zero, "Zero"),
  KBD_NAME_ENTRY(NUMBER, Zero, "NUMBER_Zero"),

  KBD_NAME_ENTRY(NUMBER, One, "One"),
  KBD_NAME_ENTRY(NUMBER, One, "NUMBER_One"),

  KBD_NAME_ENTRY(NUMBER, Two, "Two"),
  KBD_NAME_ENTRY(NUMBER, Two, "NUMBER_Two"),

  KBD_NAME_ENTRY(NUMBER, Three, "Three"),
  KBD_NAME_ENTRY(NUMBER, Three, "NUMBER_Three"),

  KBD_NAME_ENTRY(NUMBER, Four, "Four"),
  KBD_NAME_ENTRY(NUMBER, Four, "NUMBER_Four"),

  KBD_NAME_ENTRY(NUMBER, Five, "Five"),
  KBD_NAME_ENTRY(NUMBER, Five, "NUMBER_Five"),

  KBD_NAME_ENTRY(NUMBER, Six, "Six"),
  KBD_NAME_ENTRY(NUMBER, Six, "NUMBER_Six"),

  KBD_NAME_ENTRY(NUMBER, Seven, "Seven"),
  KBD_NAME_ENTRY(NUMBER, Seven, "NUMBER_Seven"),

  KBD_NAME_ENTRY(NUMBER, Eight, "Eight"),
  KBD_NAME_ENTRY(NUMBER, Eight, "NUMBER_Eight"),

  KBD_NAME_ENTRY(NUMBER, Nine, "Nine"),
  KBD_NAME_ENTRY(NUMBER, Nine, "NUMBER_Nine"),

  KBD_NAME_ENTRY(SYMBOL, Space, "Space"),
  KBD_NAME_ENTRY(SYMBOL, Space, "SYMBOL_Space"),

  KBD_NAME_ENTRY(SYMBOL, Grave, "Grave"),
  KBD_NAME_ENTRY(SYMBOL, Grave, "SYMBOL_Grave"),

  KBD_NAME_ENTRY(SYMBOL, Backslash, "Backslash"),
  KBD_NAME_ENTRY(SYMBOL, Backslash, "SYMBOL_Backslash"),

  KBD_NAME_ENTRY(SYMBOL, Minus, "Minus"),
  KBD_NAME_ENTRY(SYMBOL, Minus, "SYMBOL_Minus"),

  KBD_NAME_ENTRY(SYMBOL, Equals, "Equals"),
  KBD_NAME_ENTRY(SYMBOL, Equals, "SYMBOL_Equals"),

  KBD_NAME_ENTRY(SYMBOL, LeftBracket, "LeftBracket"),
  KBD_NAME_ENTRY(SYMBOL, LeftBracket, "SYMBOL_LeftBracket"),

  KBD_NAME_ENTRY(SYMBOL, RightBracket, "RightBracket"),
  KBD_NAME_ENTRY(SYMBOL, RightBracket, "SYMBOL_RightBracket"),

  KBD_NAME_ENTRY(SYMBOL, Semicolon, "Semicolon"),
  KBD_NAME_ENTRY(SYMBOL, Semicolon, "SYMBOL_Semicolon"),

  KBD_NAME_ENTRY(SYMBOL, Apostrophe, "Apostrophe"),
  KBD_NAME_ENTRY(SYMBOL, Apostrophe, "SYMBOL_Apostrophe"),

  KBD_NAME_ENTRY(SYMBOL, Comma, "Comma"),
  KBD_NAME_ENTRY(SYMBOL, Comma, "SYMBOL_Comma"),

  KBD_NAME_ENTRY(SYMBOL, Period, "Period"),
  KBD_NAME_ENTRY(SYMBOL, Period, "SYMBOL_Period"),

  KBD_NAME_ENTRY(SYMBOL, Slash, "Slash"),
  KBD_NAME_ENTRY(SYMBOL, Slash, "SYMBOL_Slash"),

  KBD_NAME_ENTRY(SYMBOL, Europe2, "Europe2"),

  KBD_NAME_ENTRY(ACTION, Escape, "Escape"),
  KBD_NAME_ENTRY(ACTION, Escape, "ACTION_Escape"),

  KBD_NAME_ENTRY(ACTION, Enter, "Enter"),
  KBD_NAME_ENTRY(ACTION, Enter, "ACTION_Enter"),

  KBD_NAME_ENTRY(ACTION, Tab, "Tab"),
  KBD_NAME_ENTRY(ACTION, Tab, "ACTION_Tab"),

  KBD_NAME_ENTRY(ACTION, DeleteBackward, "DeleteBackward"),
  KBD_NAME_ENTRY(ACTION, DeleteBackward, "ACTION_DeleteBackward"),

  KBD_NAME_ENTRY(ACTION, Insert, "Insert"),
  KBD_NAME_ENTRY(ACTION, Insert, "ACTION_Insert"),

  KBD_NAME_ENTRY(ACTION, DeleteForward, "DeleteForward"),
  KBD_NAME_ENTRY(ACTION, DeleteForward, "ACTION_DeleteForward"),

  KBD_NAME_ENTRY(ACTION, Home, "Home"),
  KBD_NAME_ENTRY(ACTION, Home, "ACTION_Home"),

  KBD_NAME_ENTRY(ACTION, End, "End"),
  KBD_NAME_ENTRY(ACTION, End, "ACTION_End"),

  KBD_NAME_ENTRY(ACTION, PageUp, "PageUp"),
  KBD_NAME_ENTRY(ACTION, PageUp, "ACTION_PageUp"),

  KBD_NAME_ENTRY(ACTION, PageDown, "PageDown"),
  KBD_NAME_ENTRY(ACTION, PageDown, "ACTION_PageDown"),

  KBD_NAME_ENTRY(ACTION, ArrowUp, "ArrowUp"),
  KBD_NAME_ENTRY(ACTION, ArrowUp, "ACTION_ArrowUp"),

  KBD_NAME_ENTRY(ACTION, ArrowDown, "ArrowDown"),
  KBD_NAME_ENTRY(ACTION, ArrowDown, "ACTION_ArrowDown"),

  KBD_NAME_ENTRY(ACTION, ArrowLeft, "ArrowLeft"),
  KBD_NAME_ENTRY(ACTION, ArrowLeft, "ACTION_ArrowLeft"),

  KBD_NAME_ENTRY(ACTION, ArrowRight, "ArrowRight"),
  KBD_NAME_ENTRY(ACTION, ArrowRight, "ACTION_ArrowRight"),

  KBD_NAME_ENTRY(ACTION, PrintScreen, "PrintScreen"),
  KBD_NAME_ENTRY(ACTION, PrintScreen, "ACTION_PrintScreen"),

  KBD_NAME_ENTRY(ACTION, SystemRequest, "SystemRequest"),
  KBD_NAME_ENTRY(ACTION, SystemRequest, "ACTION_SystemRequest"),

  KBD_NAME_ENTRY(ACTION, Pause, "Pause"),
  KBD_NAME_ENTRY(ACTION, Pause, "ACTION_Pause"),

  KBD_NAME_ENTRY(ACTION, GuiLeft, "GuiLeft"),
  KBD_NAME_ENTRY(ACTION, GuiLeft, "ACTION_GuiLeft"),

  KBD_NAME_ENTRY(ACTION, GuiRight, "GuiRight"),
  KBD_NAME_ENTRY(ACTION, GuiRight, "ACTION_GuiRight"),

  KBD_NAME_ENTRY(ACTION, Application, "Application"),
  KBD_NAME_ENTRY(ACTION, Application, "ACTION_Application"),

  KBD_NAME_ENTRY(ACTION, Help, "ACTION_Help"),

  KBD_NAME_ENTRY(ACTION, Stop, "ACTION_Stop"),

  KBD_NAME_ENTRY(ACTION, Props, "ACTION_Props"),

  KBD_NAME_ENTRY(ACTION, Front, "ACTION_Front"),

  KBD_NAME_ENTRY(ACTION, Open, "ACTION_Open"),

  KBD_NAME_ENTRY(ACTION, Find, "ACTION_Find"),

  KBD_NAME_ENTRY(ACTION, Again, "ACTION_Again"),

  KBD_NAME_ENTRY(ACTION, Undo, "ACTION_Undo"),

  KBD_NAME_ENTRY(ACTION, Copy, "ACTION_Copy"),

  KBD_NAME_ENTRY(ACTION, Paste, "ACTION_Paste"),

  KBD_NAME_ENTRY(ACTION, Cut, "ACTION_Cut"),

  KBD_NAME_ENTRY(ACTION, Power, "ACTION_Power"),

  KBD_NAME_ENTRY(ACTION, Sleep, "ACTION_Sleep"),

  KBD_NAME_ENTRY(ACTION, Wakeup, "ACTION_Wakeup"),

  KBD_NAME_ENTRY(ACTION, Menu, "ACTION_Menu"),

  KBD_NAME_ENTRY(ACTION, Select, "Select"),
  KBD_NAME_ENTRY(ACTION, Select, "ACTION_Select"),

  KBD_NAME_ENTRY(ACTION, Cancel, "ACTION_Cancel"),

  KBD_NAME_ENTRY(ACTION, Clear, "ACTION_Clear"),

  KBD_NAME_ENTRY(ACTION, Prior, "ACTION_Prior"),

  KBD_NAME_ENTRY(ACTION, Return, "ACTION_Return"),

  KBD_NAME_ENTRY(ACTION, Separator, "ACTION_Separator"),

  KBD_NAME_ENTRY(ACTION, Out, "ACTION_Out"),

  KBD_NAME_ENTRY(ACTION, Oper, "ACTION_Oper"),

  KBD_NAME_ENTRY(ACTION, Clear_Again, "ACTION_Clear_Again"),

  KBD_NAME_ENTRY(ACTION, CrSel_Props, "ACTION_CrSel_Props"),

  KBD_NAME_ENTRY(ACTION, ExSel, "ACTION_ExSel"),

  KBD_NAME_ENTRY(MEDIA, Mute, "MEDIA_Mute"),

  KBD_NAME_ENTRY(MEDIA, VolumeDown, "MEDIA_VolumeDown"),

  KBD_NAME_ENTRY(MEDIA, VolumeUp, "MEDIA_VolumeUp"),

  KBD_NAME_ENTRY(MEDIA, Stop, "MEDIA_Stop"),

  KBD_NAME_ENTRY(MEDIA, Play, "MEDIA_Play"),

  KBD_NAME_ENTRY(MEDIA, Record, "MEDIA_Record"),

  KBD_NAME_ENTRY(MEDIA, Pause, "MEDIA_Pause"),

  KBD_NAME_ENTRY(MEDIA, PlayPause, "MEDIA_PlayPause"),

  KBD_NAME_ENTRY(MEDIA, Previous, "MEDIA_Previous"),

  KBD_NAME_ENTRY(MEDIA, Next, "MEDIA_Next"),

  KBD_NAME_ENTRY(MEDIA, Backward, "MEDIA_Backward"),

  KBD_NAME_ENTRY(MEDIA, Forward, "MEDIA_Forward"),

  KBD_NAME_ENTRY(MEDIA, Eject, "MEDIA_Eject"),

  KBD_NAME_ENTRY(MEDIA, Close, "MEDIA_Close"),

  KBD_NAME_ENTRY(MEDIA, EjectClose, "MEDIA_EjectClose"),

  KBD_NAME_ENTRY(FUNCTION, F1, "F1"),
  KBD_NAME_ENTRY(FUNCTION, F1, "FUNCTION_F1"),

  KBD_NAME_ENTRY(FUNCTION, F2, "F2"),
  KBD_NAME_ENTRY(FUNCTION, F2, "FUNCTION_F2"),

  KBD_NAME_ENTRY(FUNCTION, F3, "F3"),
  KBD_NAME_ENTRY(FUNCTION, F3, "FUNCTION_F3"),

  KBD_NAME_ENTRY(FUNCTION, F4, "F4"),
  KBD_NAME_ENTRY(FUNCTION, F4, "FUNCTION_F4"),

  KBD_NAME_ENTRY(FUNCTION, F5, "F5"),
  KBD_NAME_ENTRY(FUNCTION, F5, "FUNCTION_F5"),

  KBD_NAME_ENTRY(FUNCTION, F6, "F6"),
  KBD_NAME_ENTRY(FUNCTION, F6, "FUNCTION_F6"),

  KBD_NAME_ENTRY(FUNCTION, F7, "F7"),
  KBD_NAME_ENTRY(FUNCTION, F7, "FUNCTION_F7"),

  KBD_NAME_ENTRY(FUNCTION, F8, "F8"),
  KBD_NAME_ENTRY(FUNCTION, F8, "FUNCTION_F8"),

  KBD_NAME_ENTRY(FUNCTION, F9, "F9"),
  KBD_NAME_ENTRY(FUNCTION, F9, "FUNCTION_F9"),

  KBD_NAME_ENTRY(FUNCTION, F10, "F10"),
  KBD_NAME_ENTRY(FUNCTION, F10, "FUNCTION_F10"),

  KBD_NAME_ENTRY(FUNCTION, F11, "F11"),
  KBD_NAME_ENTRY(FUNCTION, F11, "FUNCTION_F11"),

  KBD_NAME_ENTRY(FUNCTION, F12, "F12"),
  KBD_NAME_ENTRY(FUNCTION, F12, "FUNCTION_F12"),

  KBD_NAME_ENTRY(FUNCTION, F13, "F13"),
  KBD_NAME_ENTRY(FUNCTION, F13, "FUNCTION_F13"),

  KBD_NAME_ENTRY(FUNCTION, F14, "F14"),
  KBD_NAME_ENTRY(FUNCTION, F14, "FUNCTION_F14"),

  KBD_NAME_ENTRY(FUNCTION, F15, "F15"),
  KBD_NAME_ENTRY(FUNCTION, F15, "FUNCTION_F15"),

  KBD_NAME_ENTRY(FUNCTION, F16, "F16"),
  KBD_NAME_ENTRY(FUNCTION, F16, "FUNCTION_F16"),

  KBD_NAME_ENTRY(FUNCTION, F17, "F17"),
  KBD_NAME_ENTRY(FUNCTION, F17, "FUNCTION_F17"),

  KBD_NAME_ENTRY(FUNCTION, F18, "F18"),
  KBD_NAME_ENTRY(FUNCTION, F18, "FUNCTION_F18"),

  KBD_NAME_ENTRY(FUNCTION, F19, "F19"),
  KBD_NAME_ENTRY(FUNCTION, F19, "FUNCTION_F19"),

  KBD_NAME_ENTRY(FUNCTION, F20, "F20"),
  KBD_NAME_ENTRY(FUNCTION, F20, "FUNCTION_F20"),

  KBD_NAME_ENTRY(FUNCTION, F21, "F21"),
  KBD_NAME_ENTRY(FUNCTION, F21, "FUNCTION_F21"),

  KBD_NAME_ENTRY(FUNCTION, F22, "F22"),
  KBD_NAME_ENTRY(FUNCTION, F22, "FUNCTION_F22"),

  KBD_NAME_ENTRY(FUNCTION, F23, "F23"),
  KBD_NAME_ENTRY(FUNCTION, F23, "FUNCTION_F23"),

  KBD_NAME_ENTRY(FUNCTION, F24, "F24"),
  KBD_NAME_ENTRY(FUNCTION, F24, "FUNCTION_F24"),

  KBD_NAME_ENTRY(MODIFIER, ShiftLeft, "ShiftLeft"),
  KBD_NAME_ENTRY(MODIFIER, ShiftLeft, "MODIFIER_ShiftLeft"),

  KBD_NAME_ENTRY(MODIFIER, ShiftRight, "ShiftRight"),
  KBD_NAME_ENTRY(MODIFIER, ShiftRight, "MODIFIER_ShiftRight"),

  KBD_NAME_ENTRY(MODIFIER, ControlLeft, "ControlLeft"),
  KBD_NAME_ENTRY(MODIFIER, ControlLeft, "MODIFIER_ControlLeft"),

  KBD_NAME_ENTRY(MODIFIER, ControlRight, "ControlRight"),
  KBD_NAME_ENTRY(MODIFIER, ControlRight, "MODIFIER_ControlRight"),

  KBD_NAME_ENTRY(MODIFIER, AltLeft, "AltLeft"),
  KBD_NAME_ENTRY(MODIFIER, AltLeft, "MODIFIER_AltLeft"),

  KBD_NAME_ENTRY(MODIFIER, AltRight, "AltRight"),
  KBD_NAME_ENTRY(MODIFIER, AltRight, "MODIFIER_AltRight"),

  KBD_NAME_ENTRY(LOCK, Capitals, "CapsLock"),
  KBD_NAME_ENTRY(LOCK, Capitals, "LOCK_Capitals"),

  KBD_NAME_ENTRY(LOCK, Scroll, "ScrollLock"),
  KBD_NAME_ENTRY(LOCK, Scroll, "LOCK_Scroll"),

  KBD_NAME_ENTRY(LOCK, Numbers, "NumLock"),
  KBD_NAME_ENTRY(LOCK, Numbers, "LOCK_Numbers"),

  KBD_NAME_ENTRY(KPNUMBER, Zero, "KP0"),
  KBD_NAME_ENTRY(KPNUMBER, Zero, "KPNUMBER_Zero"),

  KBD_NAME_ENTRY(KPNUMBER, One, "KP1"),
  KBD_NAME_ENTRY(KPNUMBER, One, "KPNUMBER_One"),

  KBD_NAME_ENTRY(KPNUMBER, Two, "KP2"),
  KBD_NAME_ENTRY(KPNUMBER, Two, "KPNUMBER_Two"),

  KBD_NAME_ENTRY(KPNUMBER, Three, "KP3"),
  KBD_NAME_ENTRY(KPNUMBER, Three, "KPNUMBER_Three"),

  KBD_NAME_ENTRY(KPNUMBER, Four, "KP4"),
  KBD_NAME_ENTRY(KPNUMBER, Four, "KPNUMBER_Four"),

  KBD_NAME_ENTRY(KPNUMBER, Five, "KP5"),
  KBD_NAME_ENTRY(KPNUMBER, Five, "KPNUMBER_Five"),

  KBD_NAME_ENTRY(KPNUMBER, Six, "KP6"),
  KBD_NAME_ENTRY(KPNUMBER, Six, "KPNUMBER_Six"),

  KBD_NAME_ENTRY(KPNUMBER, Seven, "KP7"),
  KBD_NAME_ENTRY(KPNUMBER, Seven, "KPNUMBER_Seven"),

  KBD_NAME_ENTRY(KPNUMBER, Eight, "KP8"),
  KBD_NAME_ENTRY(KPNUMBER, Eight, "KPNUMBER_Eight"),

  KBD_NAME_ENTRY(KPNUMBER, Nine, "KP9"),
  KBD_NAME_ENTRY(KPNUMBER, Nine, "KPNUMBER_Nine"),

  KBD_NAME_ENTRY(KPNUMBER, A, "KPA"),
  KBD_NAME_ENTRY(KPNUMBER, A, "KPNUMBER_A"),

  KBD_NAME_ENTRY(KPNUMBER, B, "KPB"),
  KBD_NAME_ENTRY(KPNUMBER, B, "KPNUMBER_B"),

  KBD_NAME_ENTRY(KPNUMBER, C, "KPC"),
  KBD_NAME_ENTRY(KPNUMBER, C, "KPNUMBER_C"),

  KBD_NAME_ENTRY(KPNUMBER, D, "KPD"),
  KBD_NAME_ENTRY(KPNUMBER, D, "KPNUMBER_D"),

  KBD_NAME_ENTRY(KPNUMBER, E, "KPE"),
  KBD_NAME_ENTRY(KPNUMBER, E, "KPNUMBER_E"),

  KBD_NAME_ENTRY(KPNUMBER, F, "KPF"),
  KBD_NAME_ENTRY(KPNUMBER, F, "KPNUMBER_F"),

  KBD_NAME_ENTRY(KPSYMBOL, DecimalSeparator, "KPSYMBOL_DecimalSeparator"),

  KBD_NAME_ENTRY(KPSYMBOL, ThousandsSeparator, "KPSYMBOL_ThousandsSeparator"),

  KBD_NAME_ENTRY(KPSYMBOL, 00, "KPSYMBOL_00"),

  KBD_NAME_ENTRY(KPSYMBOL, 000, "KPSYMBOL_000"),

  KBD_NAME_ENTRY(KPSYMBOL, Plus, "KPPlus"),
  KBD_NAME_ENTRY(KPSYMBOL, Plus, "KPSYMBOL_Plus"),

  KBD_NAME_ENTRY(KPSYMBOL, Minus, "KPMinus"),
  KBD_NAME_ENTRY(KPSYMBOL, Minus, "KPSYMBOL_Minus"),

  KBD_NAME_ENTRY(KPSYMBOL, Multiply, "KPMultiply"),
  KBD_NAME_ENTRY(KPSYMBOL, Multiply, "KPSYMBOL_Multiply"),

  KBD_NAME_ENTRY(KPSYMBOL, Divide, "KPDivide"),
  KBD_NAME_ENTRY(KPSYMBOL, Divide, "KPSYMBOL_Divide"),

  KBD_NAME_ENTRY(KPSYMBOL, Modulo, "KPSYMBOL_Modulo"),

  KBD_NAME_ENTRY(KPSYMBOL, Equals, "KPEquals"),
  KBD_NAME_ENTRY(KPSYMBOL, Equals, "KPSYMBOL_Equals"),

  KBD_NAME_ENTRY(KPSYMBOL, Less, "KPSYMBOL_Less"),

  KBD_NAME_ENTRY(KPSYMBOL, Greater, "KPSYMBOL_Greater"),

  KBD_NAME_ENTRY(KPSYMBOL, PlusMinus, "KPSYMBOL_PlusMinus"),

  KBD_NAME_ENTRY(KPSYMBOL, LeftParenthesis, "KPSYMBOL_LeftParenthesis"),

  KBD_NAME_ENTRY(KPSYMBOL, RightParenthesis, "KPSYMBOL_RightParenthesis"),

  KBD_NAME_ENTRY(KPSYMBOL, LeftBrace, "KPSYMBOL_LeftBrace"),

  KBD_NAME_ENTRY(KPSYMBOL, RightBrace, "KPSYMBOL_RightBrace"),

  KBD_NAME_ENTRY(KPSYMBOL, BitwiseAnd, "KPSYMBOL_BitwiseAnd"),

  KBD_NAME_ENTRY(KPSYMBOL, BitwiseOr, "KPSYMBOL_BitwiseOr"),

  KBD_NAME_ENTRY(KPSYMBOL, BitwiseXor, "KPSYMBOL_BitwiseXor"),

  KBD_NAME_ENTRY(KPSYMBOL, BooleanNot, "KPSYMBOL_BooleanNot"),

  KBD_NAME_ENTRY(KPSYMBOL, BooleanAnd, "KPSYMBOL_BooleanAnd"),

  KBD_NAME_ENTRY(KPSYMBOL, BooleanOr, "KPSYMBOL_BooleanOr"),

  KBD_NAME_ENTRY(KPSYMBOL, BooleanXor, "KPSYMBOL_BooleanXor"),

  KBD_NAME_ENTRY(KPSYMBOL, Space, "KPSYMBOL_Space"),

  KBD_NAME_ENTRY(KPSYMBOL, Period, "KPPeriod"),
  KBD_NAME_ENTRY(KPSYMBOL, Period, "KPSYMBOL_Period"),

  KBD_NAME_ENTRY(KPSYMBOL, Comma, "KPSYMBOL_Comma"),

  KBD_NAME_ENTRY(KPSYMBOL, Colon, "KPSYMBOL_Colon"),

  KBD_NAME_ENTRY(KPSYMBOL, At, "KPSYMBOL_At"),

  KBD_NAME_ENTRY(KPSYMBOL, Number, "KPSYMBOL_Number"),

  KBD_NAME_ENTRY(KPSYMBOL, CurrencyUnit, "KPSYMBOL_CurrencyUnit"),

  KBD_NAME_ENTRY(KPSYMBOL, CurrencySubunit, "KPSYMBOL_CurrencySubunit"),

  KBD_NAME_ENTRY(KPACTION, Enter, "KPEnter"),
  KBD_NAME_ENTRY(KPACTION, Enter, "KPACTION_Enter"),

  KBD_NAME_ENTRY(KPACTION, Backspace, "KPACTION_Backspace"),

  KBD_NAME_ENTRY(KPACTION, Tab, "KPACTION_Tab"),

  KBD_NAME_ENTRY(KPACTION, Clear, "KPACTION_Clear"),

  KBD_NAME_ENTRY(KPACTION, ClearEntry, "KPACTION_ClearEntry"),

  KBD_NAME_ENTRY(KPACTION, MemoryClear, "KPACTION_MemoryClear"),

  KBD_NAME_ENTRY(KPACTION, MemoryStore, "KPACTION_MemoryStore"),

  KBD_NAME_ENTRY(KPACTION, MemoryRecall, "KPACTION_MemoryRecall"),

  KBD_NAME_ENTRY(KPACTION, MemoryAdd, "KPACTION_MemoryAdd"),

  KBD_NAME_ENTRY(KPACTION, MemorySubtract, "KPACTION_MemorySubtract"),

  KBD_NAME_ENTRY(KPACTION, MemoryMultiply, "KPACTION_MemoryMultiply"),

  KBD_NAME_ENTRY(KPACTION, MemoryDivide, "KPACTION_MemoryDivide"),

  KBD_NAME_ENTRY(KPACTION, Binary, "KPACTION_Binary"),

  KBD_NAME_ENTRY(KPACTION, Octal, "KPACTION_Octal"),

  KBD_NAME_ENTRY(KPACTION, Decimal, "KPACTION_Decimal"),

  KBD_NAME_ENTRY(KPACTION, Hexadecimal, "KPACTION_Hexadecimal"),

  KBD_NAME_ENTRY(BRAILLE, Space, "Space"),
  KBD_NAME_ENTRY(BRAILLE, Space, "BRAILLE_Space"),

  KBD_NAME_ENTRY(BRAILLE, Dot1, "Dot1"),
  KBD_NAME_ENTRY(BRAILLE, Dot1, "BRAILLE_Dot1"),

  KBD_NAME_ENTRY(BRAILLE, Dot2, "Dot2"),
  KBD_NAME_ENTRY(BRAILLE, Dot2, "BRAILLE_Dot2"),

  KBD_NAME_ENTRY(BRAILLE, Dot3, "Dot3"),
  KBD_NAME_ENTRY(BRAILLE, Dot3, "BRAILLE_Dot3"),

  KBD_NAME_ENTRY(BRAILLE, Dot4, "Dot4"),
  KBD_NAME_ENTRY(BRAILLE, Dot4, "BRAILLE_Dot4"),

  KBD_NAME_ENTRY(BRAILLE, Dot5, "Dot5"),
  KBD_NAME_ENTRY(BRAILLE, Dot5, "BRAILLE_Dot5"),

  KBD_NAME_ENTRY(BRAILLE, Dot6, "Dot6"),
  KBD_NAME_ENTRY(BRAILLE, Dot6, "BRAILLE_Dot6"),

  KBD_NAME_ENTRY(BRAILLE, Dot7, "Dot7"),
  KBD_NAME_ENTRY(BRAILLE, Dot7, "BRAILLE_Dot7"),

  KBD_NAME_ENTRY(BRAILLE, Dot8, "Dot8"),
  KBD_NAME_ENTRY(BRAILLE, Dot8, "BRAILLE_Dot8"),

  KBD_NAME_ENTRY(BRAILLE, Backward, "Backward"),
  KBD_NAME_ENTRY(BRAILLE, Backward, "BRAILLE_Backward"),

  KBD_NAME_ENTRY(BRAILLE, Forward, "Forward"),
  KBD_NAME_ENTRY(BRAILLE, Forward, "BRAILLE_Forward"),

  KEY_SET_ENTRY(KBD_SET_NUMBER, "NumberKey"),
  KEY_SET_ENTRY(KBD_SET_FUNCTION, "FunctionKey"),
  KEY_SET_ENTRY(KBD_SET_KPNUMBER, "KeypadNumberKey"),
  KEY_SET_ENTRY(KBD_SET_ROUTING, "RoutingKey"),
END_KEY_NAME_TABLE

KEY_NAME_TABLES_DECLARATION(keyboard) = {
  KEY_NAME_TABLE(keyboard),
  LAST_KEY_NAME_TABLE
};
