
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "BolusPresets.h"
#include "Shared.h"
#include "msp430.h"


// Allocates space on flash for the given variable
#pragma DATA_SECTION(bolusSet, ".mydata2");
#pragma DATA_ALIGN(bolusSet, 512);

// Private variables that store the basal profiles
y_bolusSet bolusSet;
y_bolusSet bolusSetLocal;

void LoadPresetsFromFlash(void);
void SavePresetsToFlash(void);

void CopyBolusPreset(y_bolus *preset1, y_bolus *preset2){
	;
}

bool EnteredBolusIsValid(y_bolus *preset){
	return true;
}
