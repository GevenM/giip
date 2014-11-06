#include "InsulinDeliveryMechanism.h"

#include "InsulinOutputCalculator.h"
#include "hardware.h"

const float k_stepVolume = 15.552; //ml/step
const int k_insulinConcentration = 10; // IU/ml

#define FORWARD  1
#define BACK  2
#define STOPPED  0

float p_insulinOutputBuffer = 0;
char stepDirection = STOPPED;
int currentStep = 0;

int GetInsulinReservoirLevel();

void DeliverPendingInsulin(){

	// Check if there's any insulin that still needs to be delivered from current program cycle
	// add this insulin to the buffer to be delivered
	p_insulinOutputBuffer += GetCurrentInsulinOutput();
	ClearCurrentInsulinOutputs(); //we don't want to add the save value multiple times

	// if the amount of insulin to be delivered is greater than or equal to the step size, deliver it.
	while( p_insulinOutputBuffer >= k_stepVolume  && GetInsulinReservoirLevel() > k_stepVolume ){
		stepDirection = FORWARD;
	}

}


int GetInsulinReservoirLevel(){
	return 10;
}



// Timer B0 interrupt service routine

#pragma vector = TIMER0_A0_VECTOR
__interrupt void myTimerISR(void)
{
	if (stepDirection == FORWARD){
		p_insulinOutputBuffer -= k_stepVolume;

		switch (currentStep){
		case 0:
			GPIO_setOutputHighOnPin( MOTOR_COIL_A1_PORT, MOTOR_COIL_A1_PIN );
			GPIO_setOutputHighOnPin( MOTOR_COIL_B1_PORT, MOTOR_COIL_B1_PIN );

			GPIO_setOutputLowOnPin( MOTOR_COIL_A2_PORT, MOTOR_COIL_A2_PIN );
			GPIO_setOutputLowOnPin( MOTOR_COIL_B2_PORT, MOTOR_COIL_B2_PIN );

			currentStep=7;
			GPIO_toggleOutputOnPin( GPIO_PORT_P4, GPIO_PIN7 );
			break;

		case 1:
			GPIO_setOutputLowOnPin( MOTOR_COIL_A1_PORT, MOTOR_COIL_A1_PIN );
			GPIO_setOutputHighOnPin( MOTOR_COIL_B1_PORT, MOTOR_COIL_B1_PIN );

			GPIO_setOutputLowOnPin( MOTOR_COIL_A2_PORT, MOTOR_COIL_A2_PIN );
			GPIO_setOutputLowOnPin( MOTOR_COIL_B2_PORT, MOTOR_COIL_B2_PIN );

			currentStep--;
			GPIO_toggleOutputOnPin( GPIO_PORT_P4, GPIO_PIN7 );

			break;
		case 2:
			GPIO_setOutputLowOnPin( MOTOR_COIL_A1_PORT, MOTOR_COIL_A1_PIN );
			GPIO_setOutputHighOnPin( MOTOR_COIL_B1_PORT, MOTOR_COIL_B1_PIN );

			GPIO_setOutputHighOnPin( MOTOR_COIL_A2_PORT, MOTOR_COIL_A2_PIN );
			GPIO_setOutputLowOnPin( MOTOR_COIL_B2_PORT, MOTOR_COIL_B2_PIN );

			GPIO_toggleOutputOnPin( GPIO_PORT_P4, GPIO_PIN7 );
			currentStep--;
			break;

		case 3:
			GPIO_setOutputLowOnPin( MOTOR_COIL_A1_PORT, MOTOR_COIL_A1_PIN );
			GPIO_setOutputLowOnPin( MOTOR_COIL_B1_PORT, MOTOR_COIL_B1_PIN );

			GPIO_setOutputHighOnPin( MOTOR_COIL_A2_PORT, MOTOR_COIL_A2_PIN );
			GPIO_setOutputLowOnPin( MOTOR_COIL_B2_PORT, MOTOR_COIL_B2_PIN );

			GPIO_toggleOutputOnPin( GPIO_PORT_P4, GPIO_PIN7 );
			currentStep--;
			break;
		case 4:
			GPIO_setOutputLowOnPin( MOTOR_COIL_A1_PORT, MOTOR_COIL_A1_PIN );
			GPIO_setOutputLowOnPin( MOTOR_COIL_B1_PORT, MOTOR_COIL_B1_PIN );

			GPIO_setOutputHighOnPin( MOTOR_COIL_A2_PORT, MOTOR_COIL_A2_PIN );
			GPIO_setOutputHighOnPin( MOTOR_COIL_B2_PORT, MOTOR_COIL_B2_PIN );

			GPIO_toggleOutputOnPin( GPIO_PORT_P4, GPIO_PIN7 );
			currentStep--;
			break;

		case 5:
			GPIO_setOutputLowOnPin( MOTOR_COIL_A1_PORT, MOTOR_COIL_A1_PIN );
			GPIO_setOutputLowOnPin( MOTOR_COIL_B1_PORT, MOTOR_COIL_B1_PIN );

			GPIO_setOutputLowOnPin( MOTOR_COIL_A2_PORT, MOTOR_COIL_A2_PIN );
			GPIO_setOutputHighOnPin( MOTOR_COIL_B2_PORT, MOTOR_COIL_B2_PIN );

			GPIO_toggleOutputOnPin( GPIO_PORT_P4, GPIO_PIN7 );
			currentStep--;
			break;
		case 6:
			GPIO_setOutputHighOnPin( MOTOR_COIL_A1_PORT, MOTOR_COIL_A1_PIN );
			GPIO_setOutputLowOnPin( MOTOR_COIL_B1_PORT, MOTOR_COIL_B1_PIN );

			GPIO_setOutputLowOnPin( MOTOR_COIL_A2_PORT, MOTOR_COIL_A2_PIN );
			GPIO_setOutputHighOnPin( MOTOR_COIL_B2_PORT, MOTOR_COIL_B2_PIN );

			GPIO_toggleOutputOnPin( GPIO_PORT_P4, GPIO_PIN7 );
			currentStep--;
			break;
		case 7:
			GPIO_setOutputHighOnPin( MOTOR_COIL_A1_PORT, MOTOR_COIL_A1_PIN );
			GPIO_setOutputLowOnPin( MOTOR_COIL_B1_PORT, MOTOR_COIL_B1_PIN );

			GPIO_setOutputLowOnPin( MOTOR_COIL_A2_PORT, MOTOR_COIL_A2_PIN );
			GPIO_setOutputLowOnPin( MOTOR_COIL_B2_PORT, MOTOR_COIL_B2_PIN );

			GPIO_toggleOutputOnPin( GPIO_PORT_P4, GPIO_PIN7 );
			currentStep--;
			break;
		default: currentStep=0; break;
		}
	} else if ( i_sensor1Btn ){
		switch (currentStep){
		case 0:
			GPIO_setOutputHighOnPin( MOTOR_COIL_A1_PORT, MOTOR_COIL_A1_PIN );
			GPIO_setOutputHighOnPin( MOTOR_COIL_B1_PORT, MOTOR_COIL_B1_PIN );

			GPIO_setOutputLowOnPin( MOTOR_COIL_A2_PORT, MOTOR_COIL_A2_PIN );
			GPIO_setOutputLowOnPin( MOTOR_COIL_B2_PORT, MOTOR_COIL_B2_PIN );

			currentStep++;
			GPIO_toggleOutputOnPin( GPIO_PORT_P4, GPIO_PIN7 );
			break;

		case 1:
			GPIO_setOutputLowOnPin( MOTOR_COIL_A1_PORT, MOTOR_COIL_A1_PIN );
			GPIO_setOutputHighOnPin( MOTOR_COIL_B1_PORT, MOTOR_COIL_B1_PIN );

			GPIO_setOutputLowOnPin( MOTOR_COIL_A2_PORT, MOTOR_COIL_A2_PIN );
			GPIO_setOutputLowOnPin( MOTOR_COIL_B2_PORT, MOTOR_COIL_B2_PIN );

			currentStep++;
			GPIO_toggleOutputOnPin( GPIO_PORT_P4, GPIO_PIN7 );

			break;
		case 2:
			GPIO_setOutputLowOnPin( MOTOR_COIL_A1_PORT, MOTOR_COIL_A1_PIN );
			GPIO_setOutputHighOnPin( MOTOR_COIL_B1_PORT, MOTOR_COIL_B1_PIN );

			GPIO_setOutputHighOnPin( MOTOR_COIL_A2_PORT, MOTOR_COIL_A2_PIN );
			GPIO_setOutputLowOnPin( MOTOR_COIL_B2_PORT, MOTOR_COIL_B2_PIN );

			GPIO_toggleOutputOnPin( GPIO_PORT_P4, GPIO_PIN7 );
			currentStep++;
			break;

		case 3:
			GPIO_setOutputLowOnPin( MOTOR_COIL_A1_PORT, MOTOR_COIL_A1_PIN );
			GPIO_setOutputLowOnPin( MOTOR_COIL_B1_PORT, MOTOR_COIL_B1_PIN );

			GPIO_setOutputHighOnPin( MOTOR_COIL_A2_PORT, MOTOR_COIL_A2_PIN );
			GPIO_setOutputLowOnPin( MOTOR_COIL_B2_PORT, MOTOR_COIL_B2_PIN );

			GPIO_toggleOutputOnPin( GPIO_PORT_P4, GPIO_PIN7 );
			currentStep++;
			break;
		case 4:
			GPIO_setOutputLowOnPin( MOTOR_COIL_A1_PORT, MOTOR_COIL_A1_PIN );
			GPIO_setOutputLowOnPin( MOTOR_COIL_B1_PORT, MOTOR_COIL_B1_PIN );

			GPIO_setOutputHighOnPin( MOTOR_COIL_A2_PORT, MOTOR_COIL_A2_PIN );
			GPIO_setOutputHighOnPin( MOTOR_COIL_B2_PORT, MOTOR_COIL_B2_PIN );

			GPIO_toggleOutputOnPin( GPIO_PORT_P4, GPIO_PIN7 );
			currentStep++;
			break;

		case 5:
			GPIO_setOutputLowOnPin( MOTOR_COIL_A1_PORT, MOTOR_COIL_A1_PIN );
			GPIO_setOutputLowOnPin( MOTOR_COIL_B1_PORT, MOTOR_COIL_B1_PIN );

			GPIO_setOutputLowOnPin( MOTOR_COIL_A2_PORT, MOTOR_COIL_A2_PIN );
			GPIO_setOutputHighOnPin( MOTOR_COIL_B2_PORT, MOTOR_COIL_B2_PIN );

			GPIO_toggleOutputOnPin( GPIO_PORT_P4, GPIO_PIN7 );
			currentStep++;
			break;
		case 6:
			GPIO_setOutputHighOnPin( MOTOR_COIL_A1_PORT, MOTOR_COIL_A1_PIN );
			GPIO_setOutputLowOnPin( MOTOR_COIL_B1_PORT, MOTOR_COIL_B1_PIN );

			GPIO_setOutputLowOnPin( MOTOR_COIL_A2_PORT, MOTOR_COIL_A2_PIN );
			GPIO_setOutputHighOnPin( MOTOR_COIL_B2_PORT, MOTOR_COIL_B2_PIN );

			GPIO_toggleOutputOnPin( GPIO_PORT_P4, GPIO_PIN7 );
			currentStep++;
			break;
		case 7:
			GPIO_setOutputHighOnPin( MOTOR_COIL_A1_PORT, MOTOR_COIL_A1_PIN );
			GPIO_setOutputLowOnPin( MOTOR_COIL_B1_PORT, MOTOR_COIL_B1_PIN );

			GPIO_setOutputLowOnPin( MOTOR_COIL_A2_PORT, MOTOR_COIL_A2_PIN );
			GPIO_setOutputLowOnPin( MOTOR_COIL_B2_PORT, MOTOR_COIL_B2_PIN );

			GPIO_toggleOutputOnPin( GPIO_PORT_P4, GPIO_PIN7 );
			currentStep=0;
			break;
		default: currentStep=0; break;
		}
	}
}


