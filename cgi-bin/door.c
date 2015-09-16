#include <wiringPi.h>
#include "gpio_layout_definitions.h"

int main (void)
{
	wiringPiSetup () ;
	pinMode (gpioDoor, OUTPUT) ;
	
	//enable relay, pause, disable relay, pause
	digitalWrite (gpioDoor, HIGH);
	delay (500) ;
	
	digitalWrite (gpioDoor, LOW);
	delay (500) ;
	return 0 ;
}