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

#include "serial_internal.h"

BEGIN_SERIAL_BAUD_TABLE
#ifdef B50
  {50, B50},
#endif /* B50 */

#ifdef B75
  {75, B75},
#endif /* B75 */

#ifdef B110
  {110, B110},
#endif /* B110 */

#ifdef B134
  {134, B134},
#endif /* B134 */

#ifdef B150
  {150, B150},
#endif /* B150 */

#ifdef B200
  {200, B200},
#endif /* B200 */

#ifdef B300
  {300, B300},
#endif /* B300 */

#ifdef B600
  {600, B600},
#endif /* B600 */

#ifdef B1200
  {1200, B1200},
#endif /* B1200 */

#ifdef B1800
  {1800, B1800},
#endif /* B1800 */

#ifdef B2400
  {2400, B2400},
#endif /* B2400 */

#ifdef B4800
  {4800, B4800},
#endif /* B4800 */

#ifdef B9600
  {9600, B9600},
#endif /* B9600 */

#ifdef B19200
  {19200, B19200},
#endif /* B19200 */

#ifdef B38400
  {38400, B38400},
#endif /* B38400 */

#ifdef B57600
  {57600, B57600},
#endif /* B57600 */

#ifdef B115200
  {115200, B115200},
#endif /* B115200 */

#ifdef B230400
  {230400, B230400},
#endif /* B230400 */

#ifdef B460800
  {460800, B460800},
#endif /* B460800 */

#ifdef B500000
  {500000, B500000},
#endif /* B500000 */

#ifdef B576000
  {576000, B576000},
#endif /* B576000 */

#ifdef B921600
  {921600, B921600},
#endif /* B921600 */

#ifdef B1000000
  {1000000, B1000000},
#endif /* B1000000 */

#ifdef B1152000
  {1152000, B1152000},
#endif /* B1152000 */

#ifdef B1500000
  {1500000, B1500000},
#endif /* B1500000 */

#ifdef B2000000
  {2000000, B2000000},
#endif /* B2000000 */

#ifdef B2500000
  {2500000, B2500000},
#endif /* B2500000 */

#ifdef B3000000
  {3000000, B3000000},
#endif /* B3000000 */

#ifdef B3500000
  {3500000, B3500000},
#endif /* B3500000 */

#ifdef B4000000
  {4000000, B4000000},
#endif /* B4000000 */
END_SERIAL_BAUD_TABLE

void
serialPutInitialAttributes (SerialAttributes *attributes) {
  attributes->c_cflag = CREAD | CLOCAL | CS8;
  attributes->c_iflag = IGNPAR | IGNBRK;

#ifdef IEXTEN
  attributes->c_lflag |= IEXTEN;
#endif /* IEXTEN */

#ifdef _POSIX_VDISABLE
  if (_POSIX_VDISABLE) {
    int i;
    for (i=0; i<NCCS; ++i) {
      if (i == VTIME) continue;
      if (i == VMIN) continue;
      attributes->c_cc[i] = _POSIX_VDISABLE;
    }
  }
#endif /* _POSIX_VDISABLE */
}

int
serialPutSpeed (SerialDevice *serial, SerialSpeed speed) {
  if (cfsetospeed(&serial->pendingAttributes, speed) != -1) {
    if (cfsetispeed(&serial->pendingAttributes, speed) != -1) {
      return 1;
    } else {
      logSystemError("cfsetispeed");
    }
  } else {
    logSystemError("cfsetospeed");
  }

  return 0;
}

int
serialPutDataBits (SerialAttributes *attributes, unsigned int bits) {
  tcflag_t size;

  switch (bits) {
#ifdef CS5
    case 5: size = CS5; break;
#endif /* CS5 */

#ifdef CS6
    case 6: size = CS6; break;
#endif /* CS6 */

#ifdef CS7
    case 7: size = CS7; break;
#endif /* CS7 */

#ifdef CS8
    case 8: size = CS8; break;
#endif /* CS8 */

    default:
      return 0;
  }

  attributes->c_cflag &= ~CSIZE;
  attributes->c_cflag |= size;
  return 1;
}

int
serialPutStopBits (SerialAttributes *attributes, SerialStopBits bits) {
  if (bits == SERIAL_STOP_1) {
    attributes->c_cflag &= ~CSTOPB;
  } else if (bits == SERIAL_STOP_2) {
    attributes->c_cflag |= CSTOPB;
  } else {
    return 0;
  }

  return 1;
}

int
serialPutParity (SerialAttributes *attributes, SerialParity parity) {
  attributes->c_cflag &= ~(PARENB | PARODD);

#ifdef PARSTK
  attributes->c_cflag &= ~PARSTK;
#endif /* PARSTK */

  if (parity != SERIAL_PARITY_NONE) {
    if (parity == SERIAL_PARITY_ODD) {
      attributes->c_cflag |= PARODD;
    } else

#ifdef PARSTK
    if (parity == SERIAL_PARITY_SPACE) {
      attributes->c_cflag |= PARSTK;
    } else

    if (parity == SERIAL_PARITY_MARK) {
      attributes->c_cflag |= PARSTK | PARODD;
    } else
#endif /* PARSTK */

    if (parity != SERIAL_PARITY_EVEN)  {
      return 0;
    }

    attributes->c_cflag |= PARENB;
  }

  return 1;
}

SerialFlowControl
serialPutFlowControl (SerialAttributes *attributes, SerialFlowControl flow) {
  typedef struct {
    tcflag_t *field;
    tcflag_t flag;
    SerialFlowControl flow;
  } FlowControlEntry;

  const FlowControlEntry flowControlTable[] = {
#ifdef CRTSCTS
    {&attributes->c_cflag, CRTSCTS, SERIAL_FLOW_INPUT_RTS | SERIAL_FLOW_OUTPUT_CTS},
#endif /* CRTSCTS */

#ifdef IHFLOW
    {&attributes->c_cflag, IHFLOW, SERIAL_FLOW_INPUT_RTS},
#endif /* IHFLOW */

#ifdef OHFLOW
    {&attributes->c_cflag, OHFLOW, SERIAL_FLOW_OUTPUT_CTS},
#endif /* OHFLOW */

#ifdef IXOFF
    {&attributes->c_iflag, IXOFF, SERIAL_FLOW_INPUT_XON},
#endif /* IXOFF */

#ifdef IXON
    {&attributes->c_iflag, IXON, SERIAL_FLOW_OUTPUT_XON},
#endif /* IXON */

    {NULL, 0, 0}
  };
  const FlowControlEntry *entry = flowControlTable;

  while (entry->field) {
    if ((flow & entry->flow) == entry->flow) {
      flow &= ~entry->flow;
      *entry->field |= entry->flag;
    } else if (!(flow & entry->flow)) {
      *entry->field &= ~entry->flag;
    }

    entry += 1;
  }

  return flow;
}

void
serialPutModemState (SerialAttributes *attributes, int enabled) {
  if (enabled) {
    attributes->c_cflag &= ~CLOCAL;
  } else {
    attributes->c_cflag |= CLOCAL;
  }
}
