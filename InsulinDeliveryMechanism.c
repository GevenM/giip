#include "InsulinDeliveryMechanism.h"
#include "InsulinReservoir.h"

#include "InsulinOutputCalculator.h"
#include "hardware.h"
#include "msp430.h"

const float k_stepVolume = 15.552; //ml/step *3600


#define FORWARD  1
#define BACKWARD  2
#define STOPPED  0

float p_insulinOutputBuffer = 0;
char stepDirection = STOPPED;
char forceDirection = STOPPED;

int currentStep = 0;

void InitInsulinDeliveryMechanism(){
    // initialize Timer0_A for motors
    TA0CCR0 = 3000;  // set up terminal count
    TA0CTL = TASSEL_2 + ID_3 + MC_1; // configure and start timer

    TA0CCTL0 = CCIE;   // enable timer interrupts
    __enable_interrupt();      // enable interrupts

}

float GetInsulinOutputBuffer(){
	return p_insulinOutputBuffer;
}

void DeliverPendingInsulin(){

	// Check if there's any insulin that still needs to be delivered from current program cycle
	// add this insulin to the buffer to be delivered
	p_insulinOutputBuffer += GetCurrentInsulinOutput();
	ClearCurrentInsulinOutputs(); //we don't want to add the same value multiple times


	// if the amount of insulin to be delivered is greater than or equal to the step size, deliver it. Also Check if there's enough insulin.
	if( p_insulinOutputBuffer >= k_stepVolume  && GetInsulinReservoirLevelInIU() >= k_stepVolume ){
		stepDirection = FORWARD;
	} else {
		stepDirection = STOPPED;
	}
}

void EnableInsulinDeliveryMechanism(){
	GPIO_setOutputHighOnPin( MOTOR_ENABLE_PORT, MOTOR_ENABLE_PIN );
}

void DisableInsulinDeliveryMechanism(){
	GPIO_setOutputLowOnPin( MOTOR_ENABLE_PORT, MOTOR_ENABLE_PIN );
}


void ForceMotorForward(){
	if ( GetInsulinReservoirLevelInPercent() >= 1 ) {
		forceDirection = FORWARD;
	} else {
		forceDirection = STOPPED;
	}
}

void ForceMotorBackward(){
	if ( GetInsulinReservoirLevelInPercent() <= 99 ) {
		forceDirection = BACKWARD;
	} else {
		forceDirection = STOPPED;
	}
}

void ForceMotorStop(){
	forceDirection = STOPPED;
}
// Timer A0 interrupt service routine

#pragma vector = TIMER0_A0_VECTOR
__interrupt void myTimerISR(void)
{
	if ( stepDirection == FORWARD || forceDirection == FORWARD ){
		p_insulinOutputBuffer -= k_stepVolume;

		// Move forward using full steps, one coil on at a time.
		switch ( currentStep ){
		case 0:
			GPIO_setOutputLowOnPin( MOTOR_COIL_A1_PORT, MOTOR_COIL_A1_PIN );
			GPIO_setOutputLowOnPin( MOTOR_COIL_B1_PORT, MOTOR_COIL_B1_PIN );
			GPIO_setOutputLowOnPin( MOTOR_COIL_A2_PORT, MOTOR_COIL_A2_PIN );
			GPIO_setOutputHighOnPin( MOTOR_COIL_B2_PORT, MOTOR_COIL_B2_PIN );

			currentStep++;
			GPIO_toggleOutputOnPin( GPIO_PORT_P4, GPIO_PIN7 );

			break;

		case 1:
			GPIO_setOutputLowOnPin( MOTOR_COIL_A1_PORT, MOTOR_COIL_A1_PIN );
			GPIO_setOutputLowOnPin( MOTOR_COIL_B1_PORT, MOTOR_COIL_B1_PIN );
			GPIO_setOutputHighOnPin( MOTOR_COIL_A2_PORT, MOTOR_COIL_A2_PIN );
			GPIO_setOutputLowOnPin( MOTOR_COIL_B2_PORT, MOTOR_COIL_B2_PIN );

			currentStep++;
			GPIO_toggleOutputOnPin( GPIO_PORT_P4, GPIO_PIN7 );
			break;
		case 2:
			GPIO_setOutputLowOnPin( MOTOR_COIL_A1_PORT, MOTOR_COIL_A1_PIN );
			GPIO_setOutputHighOnPin( MOTOR_COIL_B1_PORT, MOTOR_COIL_B1_PIN );
			GPIO_setOutputLowOnPin( MOTOR_COIL_A2_PORT, MOTOR_COIL_A2_PIN );
			GPIO_setOutputLowOnPin( MOTOR_COIL_B2_PORT, MOTOR_COIL_B2_PIN );

			currentStep++;
			GPIO_toggleOutputOnPin( GPIO_PORT_P4, GPIO_PIN7 );
			break;
		case 3:
			GPIO_setOutputHighOnPin( MOTOR_COIL_A1_PORT, MOTOR_COIL_A1_PIN );
			GPIO_setOutputLowOnPin( MOTOR_COIL_B1_PORT, MOTOR_COIL_B1_PIN );
			GPIO_setOutputLowOnPin( MOTOR_COIL_A2_PORT, MOTOR_COIL_A2_PIN );
			GPIO_setOutputLowOnPin( MOTOR_COIL_B2_PORT, MOTOR_COIL_B2_PIN );

			currentStep = 0;
			GPIO_toggleOutputOnPin( GPIO_PORT_P4, GPIO_PIN7 );
			break;
		default: currentStep = 0; break;
		}
		stepDirection = STOPPED;

	} else if ( stepDirection == BACKWARD || forceDirection == BACKWARD ){
		switch ( currentStep ){
		case 0:
			GPIO_setOutputLowOnPin( MOTOR_COIL_A1_PORT, MOTOR_COIL_A1_PIN );
			GPIO_setOutputLowOnPin( MOTOR_COIL_B1_PORT, MOTOR_COIL_B1_PIN );
			GPIO_setOutputLowOnPin( MOTOR_COIL_A2_PORT, MOTOR_COIL_A2_PIN );
			GPIO_setOutputHighOnPin( MOTOR_COIL_B2_PORT, MOTOR_COIL_B2_PIN );

			currentStep = 3;
			GPIO_toggleOutputOnPin( GPIO_PORT_P4, GPIO_PIN7 );
			break;

		case 1:
			GPIO_setOutputLowOnPin( MOTOR_COIL_A1_PORT, MOTOR_COIL_A1_PIN );
			GPIO_setOutputLowOnPin( MOTOR_COIL_B1_PORT, MOTOR_COIL_B1_PIN );
			GPIO_setOutputHighOnPin( MOTOR_COIL_A2_PORT, MOTOR_COIL_A2_PIN );
			GPIO_setOutputLowOnPin( MOTOR_COIL_B2_PORT, MOTOR_COIL_B2_PIN );

			currentStep--;
			GPIO_toggleOutputOnPin( GPIO_PORT_P4, GPIO_PIN7 );
			break;
		case 2:
			GPIO_setOutputLowOnPin( MOTOR_COIL_A1_PORT, MOTOR_COIL_A1_PIN );
			GPIO_setOutputHighOnPin( MOTOR_COIL_B1_PORT, MOTOR_COIL_B1_PIN );
			GPIO_setOutputLowOnPin( MOTOR_COIL_A2_PORT, MOTOR_COIL_A2_PIN );
			GPIO_setOutputLowOnPin( MOTOR_COIL_B2_PORT, MOTOR_COIL_B2_PIN );

			currentStep--;
			GPIO_toggleOutputOnPin( GPIO_PORT_P4, GPIO_PIN7 );
			break;
		case 3:
			GPIO_setOutputHighOnPin( MOTOR_COIL_A1_PORT, MOTOR_COIL_A1_PIN );
			GPIO_setOutputLowOnPin( MOTOR_COIL_B1_PORT, MOTOR_COIL_B1_PIN );
			GPIO_setOutputLowOnPin( MOTOR_COIL_A2_PORT, MOTOR_COIL_A2_PIN );
			GPIO_setOutputLowOnPin( MOTOR_COIL_B2_PORT, MOTOR_COIL_B2_PIN );

			currentStep--;
			GPIO_toggleOutputOnPin( GPIO_PORT_P4, GPIO_PIN7 );
			break;
		default: currentStep = 0; break;
		}
		stepDirection = STOPPED;
	}
}

/* HALF STEP CODE
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

		*/

