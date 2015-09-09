#include <stdio.h>
#include <wiringPi.h>
#include <time.h>

typedef int bool;
#define CLOSED 1
#define OPEN 0

// Sleep duration in seconds
#define SLEEP_DURATION 1

// Pin number declaration
const int swPin = 22; // Reed Switch - Broadcom pin 22, P1 pin 15

int main(void)
{
	FILE *fp = NULL;  //output file pointer
	bool previous = 2;  //previous status of the door(setting to 2 forces an update on the first loop)
	bool current = OPEN;  //current status of the door
	time_t rawTime;
	struct tm *timeInfo;
	
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
				fp = fopen("doorStatus.txt", "w");
				
				//check for errors opening the file
				if (ifp == NULL)
				{
					fprintf(stderr, "Can't open input file in.list!\n");
					exit(1);
				}
				
				//print status to the file
				fprintf(fp, "1");
				fclose(fp);
				
				//Print timestamp and door status to stdout (for logging)
				time ( &rawTime );
				timeinfo = localtime ( &rawTime );
				printf("%s : Door Closed\n", asctime(timeInfo) );
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
				fp = fopen(doorStatus.txt, w);
				
				//check for errors opening the file
				if (ifp == NULL)
				{
					fprintf(stderr, "Can't open input file in.list!\n");
					exit(1);
				}
				
				//print status to the file
				fprintf(fp, "0");
				fclose(fp);
				
				//Print timestamp and door status to stdout (for logging)
				time ( &rawTime );
				timeinfo = localtime ( &rawTime );
				printf("%s : Door Opened\n", asctime(timeInfo) );
			}
        }
		//set previous to current and sleep
		previous = current;
		sleep(sleepDuration);
    }

    return 0;
}
