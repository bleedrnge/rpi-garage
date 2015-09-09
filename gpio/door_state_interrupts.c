
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <wiringPi.h>

typedef int bool;
#define CLOSED 1
#define OPEN 0
#define TRUE 1
#define FALSE 0

// Sleep duration (seconds)
#define SLEEP_DURATION 1

// Use GPIO Pin 17, which is Pin 0 for wiringPi library
#define BUTTON_PIN 0


volatile bool status = OPEN;
volatile bool change = TRUE;

// -------------------------------------------------------------------------
// openInterrupt:  called every time an door opens
void openInterrupt(void) {
   status = OPEN;
   change = TRUE;
}

// -------------------------------------------------------------------------
// openInterrupt:  called every time an door opens
void closeInterrupt(void) {
	status = CLOSED;
	change = TRUE;
}

// -------------------------------------------------------------------------
// main
int main(void) {
	
	FILE *fp = NULL;
	time_t rawTime;
	struct tm *timeInfo;
	
	// sets up the wiringPi library
	if (wiringPiSetupGpio() < 0) {
		fprintf (stderr, "Unable to setup wiringPi: %s\n", strerror (errno));
		return 1;
	}

  // set Pin 17/0 generate an interrupt on high-to-low transitions
  // and attach myInterrupt() to the interrupt
	if ( wiringPiISR (BUTTON_PIN, INT_EDGE_FALLING, &openInterrupt) < 0 ) {
		fprintf (stderr, "Unable to setup ISR: %s\n", strerror(errno) );
		return 1;
	}
  
  // set Pin 17/0 generate an interrupt on high-to-low transitions
  // and attach myInterrupt() to the interrupt
	if ( wiringPiISR (BUTTON_PIN, INT_EDGE_RISING, &closeInterrupt) < 0 ) {
		fprintf (stderr, "Unable to setup ISR: %s\n", strerror(errno) );
		return 1;
	}

	printf("Door status monitor is running...\n");
	
  // display counter value every second.
	while(1)
	{
   	
		if(change == TRUE)
		{
			//open file for writing
			fp = fopen("doorStatus.txt", "w");
	
			//check for errors opening the file
			if (ifp == NULL)
			{
				fprintf(stderr, "Can't open input file!\n");
				return(1);
			}
				
			//print status to the file
			fprintf(fp, "%i", status);
			fclose(fp);
		
			//Print timestamp and door status to stdout (for logging)
			time ( &rawTime );
			timeinfo = localtime ( &rawTime );
			if(status == CLOSED)
			{
				printf("%s - Door Closed\n", asctime(timeinfo) );
			}
			else
			{
				printf("%s - Door Opened\n", asctime(timeinfo) );
			}
			change = FALSE;
		}
	}
	
	return 0;
}