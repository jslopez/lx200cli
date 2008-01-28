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

void Communication::getSiderealTime(int *stime)
{
        char *msg;

        this->sp->write_RS232(":GS#", 4);
        msg = this->sp->read_RS232();
	sscanf(msg, "%d:%d:%d#", &stime[0], &stime[1], &stime[2]);
}

void Communication::haltSlewing()
{
	this->sp->write_RS232(":Q#", 3);
}
