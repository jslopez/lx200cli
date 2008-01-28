/**
 * \mainpage Meade LX200 GPS client
 * \section intro_sec Introduction
 * cli_lx200 is a Meade LX200 GPS telescope client. It implements the 
 * <a href="http://www.meade.com/support/LX200CommandSet.pdf">Meade
 * Telescope Serial Command Protocol</a> (revision L, 9 Octuber 2002) by using
 * the serial port interface. The idea is the same that was used in the
 * development of cli_nex4: 
 * <a href="https://csrg.inf.utfsm.cl/twiki4/bin/view/ACS/NexstarClient">
 * NexstarClient</a>, which is to probe the communication of the telescope and 
 * the PC through the serial RS232 port.
 *
 */

/**
 * \file client.cpp
 * Main routine implementation.
 * \author Joao Lopez <jslopez@csrg.inf.utfsm.cl>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <dirent.h>
#include <Communication.h>

/** The default serial port's device file */
#define DEFAULT_PORT "/dev/ttyS0"

/** Communication object */
Communication *com = NULL;

/**
 * Leaves the program at the SIGINT signal
 * @param sig The signal received
 */ 
void leave(int sig);

/**
 * Main routine. Starts the communication through the default serial port.
 * @param args number of command-line arguments passed.
 * @param argv command-line arguments values passed.
 * @returns EXIT_SUCCESS on successful termination or EXIT_FAILURE on
 * unsuccessful termination.
 */
int main(int args, char *argv[])
{
	char serialPort[NAME_MAX];
	int time[3];

	if(args < 2){
		printf("\nUsage: %s option [value]\n\n", argv[0]);
		printf("Options availables:\n");
		printf("\tgalt\t(Get Altitude)\n");
		printf("\tgazi\t(Get Azimuth)\n");
		printf("\tgstime\t(Get Sidereal Time)\n");
		printf("\thalt\t(Halt all current slewing)\n\n");
		exit(EXIT_FAILURE);
	}

	printf("Using default port %s.\n", DEFAULT_PORT);
	strcpy(serialPort, DEFAULT_PORT);

	com = new Communication(serialPort);

	signal(SIGINT, leave);

	if (!strcmp("galt", argv[1]))
		printf("\nActual altitude: %lf\n\n", com->getAltitude());
	else if (!strcmp("gazi", argv[1]))
		printf("\nActual azimuth: %lf\n\n", com->getAzimuth());
	else if (!strcmp("gstime", argv[1])) {
		com->getSiderealTime(time);
		printf("\nSidereal time: "); 
		printf("%02d:%02d:%02d\n\n", time[0], time[1], time[2]);
	}
	else if (!strcmp("halt", argv[1])) {
		printf("\nCurrent slewing halted\n\n");
		com->haltSlewing();
	}
	else {
		printf("No such option.\n");
		exit(EXIT_FAILURE);
	}

	delete com;
	printf("Exiting cli_lx200...\n");
	exit(EXIT_SUCCESS);
}

void leave(int sig)
{
	printf("Receiving SIGINT signal... leaving now\n");
	delete com;
	printf("Exiting cli_lx200...\n");
	exit(EXIT_SUCCESS);
}
