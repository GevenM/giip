#ifndef INSULINOUTPUTCALCULATOR_H
#define INSULINOUTPUTCALCULATOR_H

#include "shared.h"

extern void InsulinOutputCalculator();
extern int GetCurrentInsulinOutput();
extern void ClearCurrentInsulinOutputs();

extern y_insulinValue f_basalOut;
extern y_insulinValue f_bolusOut;

#endif
