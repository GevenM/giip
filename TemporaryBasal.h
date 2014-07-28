#ifndef TEMPORARYBASAL_H
#define TEMPORARYBASAL_H

#include "Flash.h"
#include <stdbool.h>
#include "Shared.h"

extern void CopyTmpBasal(y_tmpBasal *fromTmpBasal, y_tmpBasal *toTmpBasal);
extern bool ActivateTemporaryBasalIsValid(y_tmpBasal *profile);
extern bool TmpBasalCompare(y_tmpBasal *profile1, y_tmpBasal *profile2);
extern bool TemporaryBasalIsActive();

#endif
