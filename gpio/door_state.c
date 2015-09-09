#include <stdio.h>    // Used for printf() statements
#include <wiringPi.h> // Include WiringPi library!
#include <time.h>

typedef int bool;
#define CLOSED 1
#define OPEN 0

// Pin number declarations. We're using the Broadcom chip pin numbers.
const int swPin = 22; // Reed Switch - Broadcom pin 22, P1 pin 15

int main(void)
{
	FILE *fp = NULL;  //output file pointer
	int sleepDuration = 1;  //duration of sleep time in seconds
	bool previous = 2;  //previous status of the door(setting to 2 forces an update on the first loop)
	bool current = OPEN;  //current status of the door
	time_t rawtime;
	struct tm *timeinfo;
	
    // Setup wiringPi:
    wiringPiSetupGpio(); // Initialize wiringPi -- using Broadcom pin numbers
    pinMode(swPin, INPUT);      // Set button as INPUT

    printf("Door status monitor is running...\n");
	
	//loop forever
    while(1)
    {
        if (digitalRead(swPin))
        {
            //Door is closed
			current = CLOSED;
			
			//only do file I/O when necessary
			if(previous != current)
			{
				//open file for writing
				fp = fopen(doorStatus.txt, w)
				
				//check for errors opening the file
				if (ifp == NULL)
				{
					fprintf(stderr, "Can't open input file in.list!\n");
					exit(1);
				}
				
				//print status to the file
				fprintf(fp, "1");
				
				//Print timestamp and door status to stdout (for logging)
				time ( &rawtime );
				timeinfo = localtime ( &rawtime );
				printf("%s : Door Closed\n")
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
				fp = fopen(doorStatus.txt, w)
				
				//check for errors opening the file
				if (ifp == NULL)
				{
					fprintf(stderr, "Can't open input file in.list!\n");
					exit(1);
				}
				
				//print status to the file
				fprintf(fp, "0");
				
				//Print timestamp and door status to stdout (for logging)
				time ( &rawtime );
				timeinfo = localtime ( &rawtime );
				printf("%s : Door Opened\n")
			}
        }
		//set previous to current and sleep
		previous = current;
		sleep(sleepDuration);
    }

    return 0;
}
