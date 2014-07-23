
#include <string.h>

#include "BolusPresets.h"
#include "Shared.h"
#include "stdlib.h"
#include "flash.h"


// Allocates space on flash for the given variable
#pragma DATA_SECTION(bolusSet, ".mydata2");
#pragma DATA_ALIGN(bolusSet, 512);

// Private variables that store the basal profiles
y_bolusSet bolusSet;
y_bolusSet bolusSetLocal;

void LoadPresetsFromFlash(void);
void SavePresetsToFlash(void);

bool BolusIsActive(){
	// Bolus is active if f_activeBolus is not the same as the empty bolus.
	if ( !strcmp( k_emptyBol.Name, f_activeBolus.Name)){
		if (k_emptyBol.Amount == f_activeBolus.Amount){
			return false;
		}
	}
	return true;
}

void InitBolusSet(){
	bolusSetLocal.NumberOfBolusPresets = 0;
	SavePresetsToFlash();
}

void CopyBolusPreset(y_bolus *fromPreset, y_bolus *toPreset){

	memcpy( toPreset->Name, fromPreset->Name, sizeof(y_bolusName) );
	// Copy the name from one profile to the other
	//strncpy( toPreset->Name, fromPreset->Name, k_bolusNameLength );

	// Copy the Amount
	toPreset->Amount = fromPreset->Amount;
}


bool EnteredBolusIsValid(y_bolus *preset){
	LoadPresetsFromFlash();

	// Check that given name is not blank
	if ( !strcmp(preset->Name, ""))
			return false;

	// Check that profile name is unique
	int i;
	for ( i = 0 ; i < bolusSetLocal.NumberOfBolusPresets ; i++ ){
		if ( PresetCompare( preset, &bolusSetLocal.Preset[ i ] ))
			return false;
	}

	// check that it's within bounds and other criteria
	return BolusIsValid( preset );
}

bool PresetCompare( y_bolus *preset1, y_bolus *preset2 ){
	// if the names match, the profiles are the same.
	if ( !strcmp( preset1->Name, preset2->Name)){
		return true;
	}
	return false;
}



void SavePresetsToFlash(void)
{
  flashEraseSegment((unsigned long)&bolusSet);

  UnlockFlash();
  bolusSet = bolusSetLocal;
  LockFlash();
}


void LoadPresetsFromFlash(void)
{
  bolusSetLocal = bolusSet;
}


// Add a bolus preset to the set of bolus presets.
int AddPresetToSet(y_bolus *preset){
	LoadPresetsFromFlash();

	// Check if maximum number of presets has been reached
	if (BolusPresetCreationAllowed()){

		// create an index variable for where to store the next preset and increment number of presets.
		char presetIndex = bolusSetLocal.NumberOfBolusPresets;
		bolusSetLocal.NumberOfBolusPresets++;

		// Copy the name into the set
		strncpy( bolusSetLocal.Preset[presetIndex].Name, preset->Name, k_bolusNameLength);

		// Copy the Amount into the set
		bolusSetLocal.Preset[ presetIndex ].Amount = preset->Amount;

		SavePresetsToFlash();
		return 1;
	}
	return -1; // creation not allowed.
}

int RemovePresetFromSet(y_bolus *preset){
	LoadPresetsFromFlash();

	// Create index to hold the location of preset to remove
	int presetIndex = GetPresetIndex(preset);
	if (presetIndex == -1) return -1; //not in set

	// If the profile to remove is the last one, simply decrement the number of profiles
	if( presetIndex == bolusSetLocal.NumberOfBolusPresets - 1 ){
		bolusSetLocal.NumberOfBolusPresets--;
		SavePresetsToFlash();
		return 1;
	}

	// If it's a profile that is not the last, move all the profiles after the one to remove up one place.
	if (presetIndex < bolusSetLocal.NumberOfBolusPresets - 1 ){
		int i;
		for (i = presetIndex; i < bolusSetLocal.NumberOfBolusPresets - 1 ; i++){
			CopyBolusPreset( &bolusSetLocal.Preset[i + 1], &bolusSetLocal.Preset[i]);
		}
		bolusSetLocal.NumberOfBolusPresets--;
		SavePresetsToFlash();
		return 1;
	}
	return -1; //should not get here, return error
}


int GetPresetIndex( y_bolus * preset){
	LoadPresetsFromFlash();

	int i = 0;
	while (strcmp(preset->Name, bolusSetLocal.Preset[i].Name) && i < k_maxNumberOfBolusPresets){
		i++;
	}

	// If profile was not found, return error code.
	if (i == k_maxNumberOfBolusPresets) return -1;

	return i;
}



bool BolusPresetCreationAllowed(){
	LoadPresetsFromFlash();

	// Check if the maximum number of presets exists, otherwise return true
	if( bolusSetLocal.NumberOfBolusPresets < k_maxNumberOfBolusPresets ){
		return true;
	}

	return false;
}

bool BolusPresetIsActive(y_bolus *preset){
	// check if the passed profile is the active profile
	return !strcmp(preset->Name, f_activeBolus.Name);
}

bool BolusPresetExists(){
	LoadPresetsFromFlash();

	if( bolusSetLocal.NumberOfBolusPresets > 0 )
		return true;

	return false;
}

int GetNumberOfBolusPresets (){
	LoadPresetsFromFlash();

	return bolusSetLocal.NumberOfBolusPresets;
}

void GetPresetName(y_bolusName *name, int index){
	LoadPresetsFromFlash();
	strncpy( *name, bolusSetLocal.Preset[index].Name, k_bolusNameLength );
}

void LoadPreset( y_bolus *preset, int index){
	LoadPresetsFromFlash();
	CopyBolusPreset(&bolusSetLocal.Preset[index], preset);
}

y_bolus CalculateBolus( y_glucose glucose, y_carbs carbs ){
	y_bolus bolus;

	strncpy( bolus.Name, "*Calculated", k_bolusNameLength );
	bolus.Amount = 3600; //Need to do calculation here.

	return bolus;
}

bool CalculatedBolusIsValid( y_bolus bolus ){

	return EnteredBolusIsValid( &bolus );

}

bool BolusIsValid( y_bolus *bolus ){

	// Check that the amount is within allowable bounds
	if ( bolus->Amount < k_minBolusBound || bolus->Amount > k_maxBolusBound ){
		return false;
	}
	if ( bolus->Amount > k_maxDailyInsulin ){
		return false;
	}

	return true;
}

