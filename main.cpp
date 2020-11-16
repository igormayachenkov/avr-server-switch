/*
 * SensorSwitch.cpp
 *
 * Created: 11/16/2020 9:54:56 PM
 * Author : Igor
 */ 

#include <avr/io.h>
#include <avr/sleep.h>

// Utilites
#define SetPin(port,pin)    port!=(1<<pin)
#define ClearPin(port,pin)  port&=~(1<<pin)


// Debug LED
#define Debug_PIN  3


int main(void)
{
	// Initialize PORTs
	DDRB  = (1<<Debug_PIN); // Debug pin under control
	PORTB = (1<<Debug_PIN); // Debug pin strong up

	
	set_sleep_mode(00);//idle
    while (1) 
    {
		sleep_mode();
    }
}

