/**
 * \file Communication.cpp
 *
 * Implements the communication with the Meade LX200 GPS telescope.
 * The communication with the device itself is done by the SerialRS232 class.
 *
 * \author Joao Lopez <jslopez@csrg.inf.utfsm.cl>
 */

#include <stdio.h>
#include <string.h>

#include "Communication.h"

Communication::Communication(char *deviceName)
{
	this->sp = new SerialRS232(deviceName);
        this->sp->write_RS232(":AA#", 4);
        this->sp->flush_RS232();
}

Communication::~Communication()
{
        delete this->sp;
}

double Communication::getAltitude()
{
        char *msg;

        this->sp->write_RS232(":GA#", 4);
        msg = this->sp->read_RS232();
	
	return sexa2double(msg);
}

double Communication::getAzimuth()
{
        char *msg;

        this->sp->write_RS232(":GZ#", 4);
        msg = this->sp->read_RS232();

	return sexa2double(msg);
}

void Communication::getDeclination(int *dec)
{
        char *msg;

        this->sp->write_RS232(":GD#", 4);
        msg = this->sp->read_RS232();
	sscanf(msg, "%d%*[^0-9]%d%*[^0-9]%d#", &dec[0], &dec[1], &dec[2]);
}

void Communication::getRA(int *ra)
{
        char *msg;

        this->sp->write_RS232(":GR#", 4);
        msg = this->sp->read_RS232();
	sscanf(msg, "%d:%d:%d#", &ra[0], &ra[1], &ra[2]);
}

void Communication::getSiderealTime(int *stime)
{
        char *msg;

        this->sp->write_RS232(":GS#", 4);
        msg = this->sp->read_RS232();
	sscanf(msg, "%d:%d:%d#", &stime[0], &stime[1], &stime[2]);
}

bool Communication::slew(char direction)
{
	switch (direction) {
		case 'n':
		case 'N':
			this->sp->write_RS232(":Mn#", 4);
			return true;
		case 's':
		case 'S':
			this->sp->write_RS232(":Ms#", 4);
			return true;
		case 'e':
		case 'E':
			this->sp->write_RS232(":Me#", 4);
			return true;
		case 'w':
		case 'W':
			this->sp->write_RS232(":Mw#", 4);
			return true;
		default:
			return false;
	}
}

void Communication::haltSlewing()
{
	this->sp->write_RS232(":Q#", 3);
}

bool Communication::goToRADec(char *ra, char *dec)
{
	int x = 0, y = 0, z = 0;
	char raCmd[12];
	char decCmd[13];
	char str[128];
	char *sign;

	/* Set ra
	:SrHH:MM:SS#
	returns 0 invalid
	returns 1 invalid
	*/
	
        strncpy (str, ra, sizeof(str)-1);
	str[sizeof(str)-1] = '\0';
        sscanf (str, "%d%*[^0-9]%d%*[^0-9]%d", &x, &y, &z);
	sprintf(raCmd, ":Sr%02d:%02d:%02d#", x, y, z);

	this->sp->write_RS232(raCmd, 12);

	/* Set declination
	:SdsDD*MM:SS#
	returns 0 Dec invalid
	returns 1 Dec accepted
	*/	
	
        strncpy (str, dec, sizeof(str)-1);
	str[sizeof(str)-1] = '\0';
        sign = strchr(str, '-');
        if (sign)
		*sign = ' ';
        sscanf (str, "%d%*[^0-9]%d%*[^0-9]%d", &x, &y, &z);
	if (sign)
		sprintf(decCmd, ":Sd-%02d*%02d:%02d#", x, y, z);
	else
		sprintf(decCmd, ":Sd+%02d*%02d:%02d#", x, y, z);

	this->sp->write_RS232(decCmd, 13);

	/* Go to target object
	:MS#
	returns 0 slew is possible
	returns 1 below horizon
	returns 2 below higher
	*/
	
	this->sp->write_RS232(":MS#", 4);

	return true;
}
