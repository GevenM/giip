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


void LoadProfilesFromFlash(void);
void SaveProfilesToFlash(void);


// Private variables that store the basal profiles
y_basalSet basalSet;
y_basalSet basalSetLocal;


void InitBasalSet(){
	basalSetLocal.numberOfBasalProfiles = 0;
	SaveProfilesToFlash();
}

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
char AddProfileToSet(y_basal *profile){
	LoadProfilesFromFlash();

	// Check if max number of profiles has been stored
	if (BasalCreationAllowed()){

		// create an index variable for where to store the next profile and increment number of profiles.
		char profileIndex = basalSetLocal.numberOfBasalProfiles;
		basalSetLocal.numberOfBasalProfiles++;

		// Copy the name into the set
		strncpy( basalSetLocal.Profile[profileIndex].Name, profile->Name, k_basalNameLength-1);

		// Copy the rates into the set
		int i;
		for (i = 0; i < k_segDay ; i++){
			basalSetLocal.Profile[profileIndex].Rate[i] = profile->Rate[i];
		}

		SaveProfilesToFlash();
		return 1;
	}

	return 0;
}



void SaveProfilesToFlash(void)
{
  flashEraseSegment((unsigned long)&basalSet);
  FLASH_UNLOCK;
  basalSet = basalSetLocal;
  FLASH_LOCK;
}


void LoadProfilesFromFlash(void)
{
  basalSetLocal = basalSet;
}

bool BasalCreationAllowed(){
	LoadProfilesFromFlash();
	if (basalSetLocal.numberOfBasalProfiles < k_maxNumberOfBasalProfiles){
		return true;
	}
	return false;
}

bool BasalProfileExists(){
	LoadProfilesFromFlash();
	if (basalSetLocal.numberOfBasalProfiles > 0){
		return true;
	}
	return false;
}

void GetProfileName(y_basalName *Name, int index){
	LoadProfilesFromFlash();
	strncpy( *Name, basalSetLocal.Profile[index].Name, k_basalNameLength-1 );
}

int GetNumberBasalProfiles(){
	LoadProfilesFromFlash();
	return basalSetLocal.numberOfBasalProfiles;
}

bool BasalProfileIsValid(y_basal *profile){
	return true;
}


extern char RemoveProfileFromSet(unsigned char profileIndex){
	LoadProfilesFromFlash();


	if(profileIndex == basalSetLocal.numberOfBasalProfiles - 1){
		basalSetLocal.numberOfBasalProfiles--;
		SaveProfilesToFlash();
		return 1;

	} else if (profileIndex < basalSetLocal.numberOfBasalProfiles - 1 ){
		int i;
		for (i = profileIndex; i < basalSetLocal.numberOfBasalProfiles - 1 ; i++){
			CopyProfile(&basalSetLocal.Profile[i + 1], &basalSetLocal.Profile[i]);
		}
		basalSetLocal.numberOfBasalProfiles--;
		SaveProfilesToFlash();
		return 1;

	}
	return 0;


}

void CopyProfile(y_basal *fromProfile, y_basal *toProfile){
	int i;

	strncpy( toProfile->Name, fromProfile->Name, k_basalNameLength-1 );

	for (i=0 ; i < k_segDay ; i++){
		toProfile->Rate[i] = fromProfile->Rate[i];
	}
}

