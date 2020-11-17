/*
 * SensorSwitch.cpp
 *
 * Created: 11/16/2020 9:54:56 PM
 * Author : Igor
 */ 

#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

// Utilites
#define SetPin(port,pin)    port|=(1<<pin)
#define ClearPin(port,pin)  port&=~(1<<pin)


// Debug LED - primitive UI
#define Debug_PIN  3
bool debugLed = true;
void applyDebugLed(){
	if(debugLed)
		SetPin(PORTB,Debug_PIN);
	else
		ClearPin(PORTB,Debug_PIN);
}


int main(void)
{
	// Initialize PORTs
	DDRB  = (1<<Debug_PIN); // Debug pin under control
	//PORTB = 0; // Initial 0

	applyDebugLed();


	// MAIN SLOW THREAD : 8-bit TIMER/COUNTER0
	// TCCR0A – Timer/Counter0 Control Register A
	TCCR0A = 0<<COM0A1 | 0<<COM0A0 //Normal port operation, OC0A/OC0B disconnected.
		| 0<<COM0B1 | 0<<COM0B0 // Normal port operation, OC0A/OC0B disconnected.
		| 0<<WGM02  | 0<<WGM01  | 0<<WGM00 ; // Normal mode
	// TCCR0B – Timer/Counter0 Control Register B
	TCCR0B = 1<<CS02 | 0<<CS01 | 1<<CS00; // Internal Clock/1024
	
	// PWM GENERATOR : 8-bit TIMER/COUNTER1

	
	// Timer/Counter Interrupt Mask Register - TIMSK
	TIMSK = 1<<TOIE0; // Overflow interrupt enable	
	
	sei(); //enable interrupts
	
	set_sleep_mode(00);//idle
    while (1) 
    {
		sleep_mode();
    }
}

//--------------------------------------------------------
// Timer/Counter-0 thread - slow thread
//#define COUNT_SKIP 120
//unsigned char countSkip = COUNT_SKIP;

ISR(TIMER0_OVF_vect){
	//if(countSkip>0) countSkip--;
	//else{
		//countSkip = COUNT_SKIP;
		
		// Toggle debug led
		debugLed = !debugLed;
		applyDebugLed();
	//}
}

