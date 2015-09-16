#include <wiringPi.h>
#include "gpio_layout_definitions.h"


int main (void)
{
	wiringPiSetup () ;
	pinMode (gpioLight, OUTPUT) ;

	//enable relay, pause, disable relay, pause
	digitalWrite (gpioLight, HIGH);
	delay (500) ;
	
	digitalWrite (gpioLight, LOW);
	delay (500) ;
	return 0 ;
}