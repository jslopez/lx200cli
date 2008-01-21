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

    printf("Using default port %s.\n", DEFAULT_PORT);
    strcpy(serialPort, DEFAULT_PORT);

    com = new Communication(serialPort);

    signal(SIGINT, leave);

    if (!strcmp("galt", argv[1]))
	com->getAltitude();
    else if (!strcmp("gdec", argv[1]))
	com->getDeclination();
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
