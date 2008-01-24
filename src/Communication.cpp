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
        this->sp->flush_RS232();
}

Communication::~Communication()
{
        delete this->sp;
}

void Communication::initializeTelescope()
{
        this->sp->write_RS232(":I#", 3);
}

void Communication::getAltitude()
{
        char *msg;

        this->sp->write_RS232(":GA#", 4);
        msg = this->sp->read_RS232();
	
	printf("%f\n", sexa2double(msg));
}

void Communication::getDeclination()
{
        char *msg;

        this->sp->write_RS232(":GD#", 4);
        msg = this->sp->read_RS232();

	printf("%f\n", sexa2double(msg));
}

void Communication::getRA()
{
        char *msg;

        this->sp->write_RS232(":GR#", 4);
        msg = this->sp->read_RS232();

        printf("%s\n", msg);
}

void Communication::getSiderealTime()
{
        char *msg;

        this->sp->write_RS232(":GS#", 4);
        msg = this->sp->read_RS232();

        printf("%s\n", msg);
}

void Communication::getTrackingRate()
{
        char *msg;

        this->sp->write_RS232(":GT#", 4);
        msg = this->sp->read_RS232();

        printf("%s\n", msg);
}

void Communication::getAzimuth()
{
        char *msg;

        this->sp->write_RS232(":GZ#", 4);
        msg = this->sp->read_RS232();

        printf("%s\n", msg);
}
