#include "BolusFunctions.h"
#include "TypesAndConstants.h"
#include <string.h>

y_bolus CalculatedBolus( y_glucose *glucose, y_carbs *carbs ){
	y_bolus bolus;

	strncpy( bolus.Name, "*Calculated", k_bolusNameLength );
	bolus.Amount = 3600; //Need to do calculation here.

	return bolus;
}
