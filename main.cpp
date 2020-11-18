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

// PWM
#define PWM_PIN 1 //PB1/OC1A
unsigned char valPWM = 6;

// Debug LED - primitive UI
#define Debug_PIN  4
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
	DDRB  = 1<<Debug_PIN | 1<<PWM_PIN; // Debug pin under control
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
	OCR1A = 18; //(MIN)6:432us 15:1.0us   23:1480us   31:1980us(MAX)  18-middle
	OCR1C = 0xFF;
	// TCCR1 – Timer/Counter1 Control Register
	TCCR1 = 1<<PWM1A // Pulse Width Modulator A Enable
	        | 1<<COM1A1 | 0<<COM1A0 // OC1A cleared on compare match. Set when TCNT1 = $00.
	        | 0<<CS13 | 1<<CS12 | 1<<CS11 | 1<<CS10; // Freq 63 Hz (period: 17ms)	
			
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
		
		//OCR1A = valPWM;
		//valPWM++;
		
		// Toggle debug led
		debugLed = !debugLed;
		applyDebugLed();
	//}
}

