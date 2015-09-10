
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <wiringPi.h>

typedef int bool;
#define CLOSED 1
#define OPEN 0
#define TRUE 1
#define FALSE 0

// Sleep duration (seconds)
#define SLEEP_DURATION 1

// Use GPIO Pin 17, which is Pin 0 for wiringPi library
#define BUTTON_PIN 22


volatile bool status = OPEN;
volatile bool change = TRUE;

// -------------------------------------------------------------------------
// openInterrupt:  called every time the door opens
void openInterrupt(void) {
   status = OPEN;
   change = TRUE;
}

// -------------------------------------------------------------------------
// closeInterrupt:  called every time the door closes
void closeInterrupt(void) {
	status = CLOSED;
	change = TRUE;
}

// -------------------------------------------------------------------------
// main
int main(void) {

	FILE *fp = NULL;
	time_t rawtime;
	struct tm *timeinfo;

	// sets up the wiringPi library
	if (wiringPiSetupGpio() < 0) {
		fprintf (stderr, "Unable to setup wiringPi: %s\n", strerror (errno));
		return 1;
	}

	// pull up resistor
	pullUpDnControl (BUTTON_PIN, PUD_UP);

	// set Pin 17/0 generate an interrupt on high-to-low transitions
	// and attach myInterrupt() to the interrupt
	if ( wiringPiISR (BUTTON_PIN, INT_EDGE_FALLING, &openInterrupt) < 0 ) {
		fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno));
		return 1;
	}

	// set Pin 17/0 generate an interrupt on high-to-low transitions
	// and attach myInterrupt() to the interrupt
	if ( wiringPiISR (BUTTON_PIN, INT_EDGE_RISING, &closeInterrupt) < 0 ) {
		fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno));
		return 1;
	}

	printf("Door status monitor is running...\n");

	while(1)
	{

		if(change == TRUE)
		{
			//open file for writing
			fp = fopen("doorStatus.txt", "w");

			//check for errors opening the file
			if (fp == NULL)
			{
				fprintf(stderr, "Can't open input file!\n");
				return(1);
			}

			//print status to the file and close the stream
			fprintf(fp, "%i", status);
			fclose(fp);

			//Print timestamp and door status to stdout (for logging)
			time ( &rawtime );
			timeinfo = localtime ( &rawtime );
			if(status == CLOSED)
			{
				printf("%s - Door Closed\n", asctime(timeinfo) );
			}
			else
			{
				printf("%s - Door Opened\n", asctime(timeinfo) );
			}

			//Reset change flag
			change = FALSE;
		}
	}

	return 0;
}
