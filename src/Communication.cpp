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

	printf("%s", msg);
}

void Communication::getDeclination()
{
	char *msg;

	this->sp->write_RS232(":GD#", 4);
	msg = this->sp->read_RS232();

	printf("%s", msg);
}

void Communication::getRA()
{
	char *msg;

	this->sp->write_RS232(":GR#", 4);
	msg = this->sp->read_RS232();

	printf("%s", msg);
}

void Communication::getSiderealTime()
{
	char *msg;

	this->sp->write_RS232(":GS#", 4);
	msg = this->sp->read_RS232();

	printf("%s", msg);
}

void Communication::getTrackingRate()
{
	char *msg;

	this->sp->write_RS232(":GT#", 4);
	msg = this->sp->read_RS232();

	printf("%s", msg);
}

void Communication::getAzimuth()
{
	char *msg;

	this->sp->write_RS232(":GZ#", 4);
	msg = this->sp->read_RS232();

	printf("%s", msg);
}
