#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "BasalProfiles.h"
#include "msp430.h"


#define FLASH_UNLOCK    FCTL3 = FWKEY; FCTL1 = FWKEY + WRT;
#define FLASH_LOCK      FCTL1 = FWKEY; FCTL3 = FWKEY +  LOCK;

// Allocates space on flash for the given variable
#pragma DATA_SECTION(basalSet, ".mydata1");
#pragma DATA_ALIGN(basalSet, 512);


void loadProfileFromFlash(void);
void saveProfileToFlash(void);


// Private variables that store the basal profiles
y_basalSet basalSet;
y_basalSet basalSetLocal;

// Takes a profile and updates the name and rates.
void CreateProfile(y_basal *me, char *Name, unsigned char Rate[]){
	//strncpy( me->Name, Name, K_NAME_LENGTH-1);

	//int i;
	//for (i = 0; i<K_RATES; i++){
	//	me->Rate[i] = Rate[i];
	//}
}

// Changes the name of the given profile with the provided name
void ChangeProfileName(y_basal *me, char * Name){
	//strncpy( me->Name, Name, K_NAME_LENGTH-1);
}

// Add a basal profile to a set of basal profiles. Takes a set and a profile as inputs. Allocates memory for profiles.
int AddProfileToSet(y_basalSet *setRoot, y_basal *profile){
/*	y_basalSet* currentProfile;
	currentProfile = setRoot;

	// If the set is empty, add the profile to the root node. otherwise traverse the list of profiles and add onto the end.
	if (currentProfile->Profile == 0){
		currentProfile->Profile = malloc(sizeof (y_basal));
		if (currentProfile->Profile ==0) return -1; //Unable to allocate memory

		CreateProfile(currentProfile->Profile, profile->Name, profile->Rate);
	} else {

		while(currentProfile->Next != 0){
			currentProfile = currentProfile->Next;
		}

		currentProfile->Next = malloc( sizeof( y_basalSet ));
		if (currentProfile->Next == 0) return -1; //Unable to allocate memory

		currentProfile->Next->Profile = malloc(sizeof (y_basal));
		if (currentProfile->Next->Profile ==0) return -1; //Unable to allocate memory

		CreateProfile(currentProfile->Next->Profile, profile->Name, profile->Rate);
		currentProfile->Next->Next = 0;
	}*/
	return 0;
}


/**********************************************************************//**
 * @brief  Stores calibration and user-config data into flash segment
 *
 * @param  none
 *
 * @return none
 *************************************************************************/
void saveProfilesToFlash(void)
{
  flashEraseSegment((unsigned long)&basalSet);
  FLASH_UNLOCK;
  basalSet = basalSetLocal;
  FLASH_LOCK;
}

/**********************************************************************//**
 * @brief  Loads calibration and user-config data from flash segment.
 *
 * @param  none
 *
 * @return none
 *************************************************************************/
void loadProfilesFromSettings(void)
{
  basalSetLocal = basalSet;
}
