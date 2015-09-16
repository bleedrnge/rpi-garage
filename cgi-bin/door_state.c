#include <stdio.h>    // Used for printf() statements
#include <wiringPi.h> // Include WiringPi library!
#include <time.h>
#include <unistd.h>
#include "gpio_layout_definitions.h"

typedef int bool;

int main(void)
{
	FILE *fp;  //output file pointer
	int sleepDuration = 1;  //duration of sleep time in seconds
	bool previous = 2;  //previous status of the door(setting to 2 forces an update on the first loop)
	bool current = OPEN;  //current status of the door
	time_t rawtime;
	struct tm * timeinfo;

	// Setup wiringPi:
	wiringPiSetupGpio(); // Initialize wiringPi -- using Broadcom pin numbers
	pinMode(gpioReedSwitch, INPUT);      // Set button as INPUT
	pullUpDnControl (gpioReedSwitch, PUD_UP);  //pull up resistor

	printf("Door status monitor is running...\n");

	//loop forever
	while(1)
	{
		if (digitalRead(gpioReedSwitch))
		{
			//Door is closed
			current = CLOSED;

			//only do file I/O when necessary
			if(previous != current)
			{
				//open file for writing
				fp = fopen("doorStatus.txt", "w");

				//check for errors opening the file
				if (fp == NULL)
				{
					fprintf(stderr, "Can't open input file!\n");
					return(1);
				}

				//print status to the file
				fprintf(fp, "1");
				fclose(fp);
				//Print timestamp and door status to stdout (for logging)
				time ( &rawtime );
				timeinfo = localtime ( &rawtime );
				printf("%s : Door Closed\n",asctime ( timeinfo ) );
			}
		}
		else
        	{
			//Door is open
			current = OPEN;
			//only do file I/O when necessary
			if(previous != current)
			{
				//open file for writing
				fp = fopen("doorStatus.txt", "w");

				//check for errors opening the file
				if (fp == NULL)
				{
					fprintf(stderr, "Can't open input file!\n");
					return(1);
				}

				//print status to the file
				fprintf(fp, "0");
				fclose(fp);
				//Print timestamp and door status to stdout (for logging)
				time ( &rawtime );
				timeinfo = localtime ( &rawtime );
				printf("%s : Door Opened\n",asctime ( timeinfo ) );
			}
		}
	//set previous to current and sleep
	previous = current;
	sleep(sleepDuration);
    }

    return 0;
}
