#ifndef TEMPORARYBASAL_H
#define TEMPORARYBASAL_H

#include "Flash.h"
#include <stdbool.h>


typedef unsigned char y_tmpBasalRate;
typedef unsigned char y_duration;

typedef struct tmpBasal{
	y_tmpBasalRate Rate;
	y_duration Duration;
} y_tmpBasal;

extern void CopyTmpBasal(y_tmpBasal *fromTmpBasal, y_tmpBasal *toTmpBasal);
extern bool ActivateTemporaryBasalIsValid(y_tmpBasal *profile);

#endif
