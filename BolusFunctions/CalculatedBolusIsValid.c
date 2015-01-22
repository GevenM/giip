#include "BolusFunctions.h"


bool CalculatedBolusIsValid( y_glucose *glucose, y_carbs *carbs ){
	y_bolus bolus;
	bolus = CalculatedBolus( glucose , carbs );

	return BolusIsValid( &bolus );
}
