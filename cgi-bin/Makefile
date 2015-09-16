CC=gcc
CFLAGS=-lwiringPi
door:
	gcc -Wall -o door.cgi door.c $(CFLAGS)

lights:
	gcc -Wall -o lights.cgi lights.c $(CFLAGS)

door_state:
	gcc -Wall -o door_state.cgi door_state.c $(CFLAGS)
	
clean:
	rm -f *.cgi
