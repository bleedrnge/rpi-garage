#include <wiringPi.h>

//pin to use for lights
#define PIN 1

int main (void)
{
	wiringPiSetup () ;
	pinMode (PIN, OUTPUT) ;
	
	//enable relay, pause, disable relay, pause
	digitalWrite (PIN, HIGH);
	delay (500) ;
	
	digitalWrite (PIN, LOW);
	delay (500) ;
	return 0 ;
}