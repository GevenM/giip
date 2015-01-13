
#include "InsulinReservoir.h"
#include "msp430.h"

const float k_insulinConcentration = 10; // IU/ml
const float k_insulinReservoirCapacity = 20; //ml
unsigned int reservoirLevel = 0;


void InitInsulinReservoirSensor(){
    // adc stuff
    REFCTL0 &= ~REFMSTR;                      // Reset REFMSTR to hand over control to
                                                // ADC12_A ref control registers
    ADC12CTL0 = ADC12SHT0_8 + ADC12REFON + ADC12ON;
                                                // Internal ref = vcc
    ADC12CTL1 = ADC12SHP;                     // enable sample timer
    ADC12MCTL0 = ADC12SREF_0 + ADC12INCH_3;  // ADC i/p ch A3
    ADC12IE = 0x001;                          // ADC_IFG upon conv result-ADCMEMO

    ADC12CTL0 |= ADC12ENC; // enables conversion
}

void UpdateInsulinReservoirSensor(){
    ADC12CTL0 &= ~ADC12SC;
    ADC12CTL0 |= ADC12SC;                   // Sampling and conversion start
}


// return the amount in IU that remains in the insulin reservoir
unsigned long GetInsulinReservoirLevelInIU(){
	if (reservoirLevel <= 100 ){
		return k_insulinReservoirCapacity * k_insulinConcentration * 3600;
	} else 	if (reservoirLevel >= 4000 ){
		return 0;
	} else {
		return ((-5.1282 * reservoirLevel ) + 20513) / 1000 * k_insulinConcentration * 3600;
	}
}


int GetInsulinReservoirLevelInPercent(){
	if ( reservoirLevel <= 100 ){
		return 100;
	} else if ( reservoirLevel >= 4000 ) {
		return 0;
	} else {
		return ((-5.1282 * reservoirLevel ) + 20513)/200;
	}
}



// Interrupt that reads the sensor.
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(ADC12_VECTOR))) ADC12ISR (void)
#else
#error Compiler not supported!
#endif
{
  switch(__even_in_range(ADC12IV,34))
  {
  case  0: break;                           // Vector  0:  No interrupt
  case  2: break;                           // Vector  2:  ADC overflow
  case  4: break;                           // Vector  4:  ADC timing overflow
  case  6:                                  // Vector  6:  ADC12IFG0
    reservoirLevel = ADC12MEM0;                       // Move results, IFG is cleared


   // __bic_SR_register_on_exit(LPM4_bits);   // Exit active CPU
    break;
  case  8: break;                           // Vector  8:  ADC12IFG1
  case 10: break;                           // Vector 10:  ADC12IFG2
  case 12: break;                           // Vector 12:  ADC12IFG3
  case 14: break;                           // Vector 14:  ADC12IFG4
  case 16: break;                           // Vector 16:  ADC12IFG5
  case 18: break;                           // Vector 18:  ADC12IFG6
  case 20: break;                           // Vector 20:  ADC12IFG7
  case 22: break;                           // Vector 22:  ADC12IFG8
  case 24: break;                           // Vector 24:  ADC12IFG9
  case 26: break;                           // Vector 26:  ADC12IFG10
  case 28: break;                           // Vector 28:  ADC12IFG11
  case 30: break;                           // Vector 30:  ADC12IFG12
  case 32: break;                           // Vector 32:  ADC12IFG13
  case 34: break;                           // Vector 34:  ADC12IFG14
  default: break;
  }
}
