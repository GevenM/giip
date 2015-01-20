#ifndef BASALPROFILES_H
#define BASALPROFILES_H

#include "../Flash.h"
#include <stdbool.h>
#include "../Shared.h"
#include "BasalTables.h"

#define k_maxNumberOfBasalProfiles 4  // at 48 segments and 12 name length, 4 profiles fit on one segment of flash

typedef struct y_basalSet{
	y_basal Profile[ k_maxNumberOfBasalProfiles ];
	char numberOfBasalProfiles;
} y_basalSet;


extern void InitBasalSet();
extern bool BasalCreationAllowed();
extern bool BasalProfileExists();
extern void GetProfileName(y_basalName *Name, int index);
extern int GetNumberBasalProfiles();

extern bool BasalProfileIsValid(y_basal *profile);
extern bool ActivateBasalProfileIsValid(y_basal *profile);
extern bool BasalProfileIsActive(y_basal *profile);
extern bool BasalIsActive();

extern int AddProfileToSet(y_basal *profile);
extern int RemoveProfileFromSet(y_basal *profile);
extern void CopyProfile(y_basal *fromProfile, y_basal *toProfile);

extern int GetProfileIndex( y_basal * profile);
void LoadProfile( y_basal *profile, int index);
extern bool ProfileCompare(y_basal *profile1, y_basal *profile2);

extern int GetCurrentTimeSegment ();
#endif
