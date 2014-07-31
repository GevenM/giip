#ifndef PRINTTMPBAS_H
#define PRINTTMPBAS_H

#include "Shared.h"
#include "Driverlib.h"
#include "grlib.h"
#include "LcdDriver/Sharp96x96.h"
#include <string.h>

extern void PrintStartTmpBas_Confirm(tContext *context);
extern void PrintStartTmpBas_Invalid(tContext *context);

#endif
