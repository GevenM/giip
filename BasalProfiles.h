#ifndef BASALPROFILES_H
#define BASALPROFILES_H

#include "Flash.h"

#define k_segDay 48
#define k_basalNameLength 12
#define k_numberOfBasalProfiles 8  // at 48 segments and 12 name length, 8 profiles fit on one segment of flash


typedef char y_basalName[k_basalNameLength];
typedef unsigned char y_basalRate[k_segDay];


typedef struct profile{
	y_basalName Name;
	y_basalRate Rate;
} y_basal;


typedef struct y_basalSet{
	y_basal Profile[k_numberOfBasalProfiles];
	char f_numberOfBasalProfiles;
} y_basalSet;


extern void CreateProfile(y_basal *me, char *Name, unsigned char Rate[]);
extern void ChangeProfileName(y_basal *me, char *Name);
int AddProfileToSet(y_basalSet *setRoot, y_basal *profile);

#endif
