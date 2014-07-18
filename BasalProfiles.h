#ifndef BASALPROFILES_H
#define BASALPROFILES_H

#include "Flash.h"
#include <stdbool.h>


#define k_segDay 48
#define k_basalNameLength 12
#define k_maxNumberOfBasalProfiles 8  // at 48 segments and 12 name length, 8 profiles fit on one segment of flash


typedef char y_basalName[k_basalNameLength+1];
typedef unsigned char y_basalRate;

typedef struct profile{
	y_basalName Name;
	y_basalRate Rate[k_segDay];
} y_basal;


typedef struct y_basalSet{
	y_basal Profile[k_maxNumberOfBasalProfiles];
	char numberOfBasalProfiles;
} y_basalSet;


extern void CreateProfile(y_basal *me, char *Name, unsigned char Rate[]);
extern void ChangeProfileName(y_basal *me, char *Name);
extern void InitBasalSet();
extern bool BasalCreationAllowed();
extern bool BasalProfileExists();
extern void GetProfileName(y_basalName *Name, int index);
extern int GetNumberBasalProfiles();

extern bool BasalProfileIsValid(y_basal *profile);
extern bool ActivateBasalProfileIsValid(y_basal *profile);
extern bool BasalProfileIsActive(y_basal *profile);

extern int AddProfileToSet(y_basal *profile);
extern int RemoveProfileFromSet(y_basal *profile);
extern void CopyProfile(y_basal *fromProfile, y_basal *toProfile);
extern int GetProfileIndex( y_basal * profile);
extern void LoadProfile( y_basal *profile, int index);
extern bool ProfileCompare(y_basal *profile1, y_basal *profile2);
#endif
