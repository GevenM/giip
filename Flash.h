#ifndef FLASH_H
#define FLASH_H

#include "msp430.h"


extern void flashEraseSegment(unsigned long FarPtr);
extern void LockFlash();
extern void UnlockFlash();

#endif
