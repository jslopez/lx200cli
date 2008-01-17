#include <stdio.h>
#include <string.h>

#include "Communication.h"

Communication::Communication(char deviceName)
{
	this->sp = new SerialRS232(devinceName);
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

char Communication::getAltitude()
{
	char *msg;

	this->sp->write_RS232(":GA#", 4);
	msg = this->sp->read_RS232();

	printf("%s", msg);
}

char Communication::getDeclination()
{
	char *msg;

	this->sp->write_RS232(":GD#", 4);
	msg = this->sp->read_RS232();

	printf("%s", msg);
}

char Communication::getRA()
{
	char *msg;

	this->sp->write_RS232(":GR#", 4);
	msg = this->sp->read_RS232();

	printf("%s", msg);
}

char Communication::getSiderealTime()
{
	char *msg;

	this->sp->write_RS232(":GS#", 4);
	msg = this->sp->read_RS232();

	printf("%s", msg);
}

char Communication::getTrackingRate()
{
	char *msg;

	this->sp->write_RS232(":GT#", 4);
	msg = this->sp->read_RS232();

	printf("%s", msg);
}

char Communication::getAzimuth()
{
	char *msg;

	this->sp->write_RS232(":GZ#", 4);
	msg = this->sp->read_RS232();

	printf("%s", msg);
}
