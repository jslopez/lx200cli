/**
 * \mainpage Meade LX200 GPS client
 */

/**
 * \file main.cpp
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

void leave(int);

int main(int args, char *argv[])
{
	char serialPort[NAME_MAX];

	if(args < 2){
		printf("\nUsage: %s [option]\n\n", argv[0]);
		printf("Options availables:\n");
		printf("\tgalt\t(Get Altitude)\n");
		printf("\tgdec\t(Get Declination)\n");
		printf("\tgra\t(Get RA)\n");
		printf("\tgazi\t(Get Azimuth)\n");
		printf("\tgstime\t(Get Sidereal Time)\n");
		printf("\tgtrack\t(Get Tracking Rate)\n\n");
		exit(EXIT_FAILURE);
	}

	printf("Using default port %s.\n", DEFAULT_PORT);
	strcpy(serialPort, DEFAULT_PORT);

	com = new Communication(serialPort);

	signal(SIGINT, leave);

	if (!strcmp("galt", argv[1]))
		com->getAltitude();
	else if (!strcmp("gdec", argv[1]))
		com->getDeclination();
	else if (!strcmp("gra", argv[1]))
		com->getRA();
	else if (!strcmp("gazi", argv[1]))
		com->getAzimuth();
	else if (!strcmp("gstime", argv[1]))
		com->getSiderealTime();
	else if (!strcmp("gtrack", argv[1]))
		com->getTrackingRate();
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
