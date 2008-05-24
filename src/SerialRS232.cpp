/******************************************************************************
 * OAN - Observatorio Astronómico Nacional
 * (c) OAN, 2004
 *
 * This code is under GNU General Public Licence (GPL).
 *
 * serialport_rs232.cpp
 *
 * who       when        what
 * --------  ----------  ----------------------------------------------
 * rbolano   2004/03/14  created
 * rtobar    2008/04/01  handling the end of the read with select()
 */

#include "SerialRS232.h"

#include <cstring>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/times.h>

SerialRS232::SerialRS232(const char * dev, const long & millisecs,
		const baudrates & baudrate, const parities & parity,
		const databits & databitsnum, const stopbits & stopbitsnum,
		const unsigned int & buflen, const int & timeout)
		throw (SerialRS232Exception &)
{
	if (index(dev, '\0') == NULL)
		throw SerialRS232Exception("[SerialRS232::SerialRS232] Device name must be null terminated");

	if (strlen(dev) < 0 || strlen(dev) > 64)
		throw SerialRS232Exception("[SerialRS232::SerialRS232] Device name incorrect length");

	if (strchr(dev, ' ') != NULL)
		throw SerialRS232Exception("[SerialRS232::SerialRS232] Device name cannot contain blank spaces");

	if ((m_port = open(dev, O_RDWR | O_NDELAY) )<0)
		throw SerialRS232Exception("[SerialRS232::SerialRS232] Error opening the device");
	
	fcntl(m_port, F_SETFL, fcntl(m_port, F_GETFL, 0) & ~O_NDELAY);

	struct termio term;

	if (ioctl(m_port, TCGETA, &term) == -1)
		throw SerialRS232Exception("[SerialRS232::SerialRS232] Error when calling ioctl (GET)");

	term.c_iflag |= IGNBRK;
	term.c_iflag &= ~(BRKINT | IGNPAR | PARMRK | INPCK | ISTRIP | INLCR | IGNCR | ICRNL | IUCLC | IXON | IXANY | IXOFF);

	term.c_oflag &= ~OPOST;

	term.c_lflag &= ~(ICANON | ISIG | ECHO);

	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 1;

	switch (stopbitsnum) {
		case stop1:
			term.c_cflag &= ~CSTOPB;
			break;
		case stop2:
			term.c_cflag |= CSTOPB;
			break;
		default:
			throw SerialRS232Exception("[SerialRS232::SerialRS232] Error setting stop bits number");
	}

	term.c_cflag &= ~CSIZE;
	switch (databitsnum) {
		case data5:
			term.c_cflag |= CS5;
			break;
		case data6:
			term.c_cflag |= CS6;
			break;
		case data7:
			term.c_cflag |= CS7;
			break;
		case data8:
			term.c_cflag |= CS8;
			break;
		default:
			throw SerialRS232Exception("[SerialRS232::SerialRS232] Error setting data bits number");
	};

	switch (parity) {
		case noparity:
			term.c_cflag &= ~PARENB;
			break;
		case odd:
			term.c_cflag |= PARENB;
			term.c_cflag |= PARODD;
			break;
		case even:
			term.c_cflag |= PARENB;
			term.c_cflag &= ~PARODD;
			break;
		default:
			throw SerialRS232Exception("[SerialRS232::SerialRS232] Error setting parity");
	}

	term.c_cflag &= ~CBAUD;

	switch (baudrate){
		case b50:
			term.c_cflag |= B50;
			break;
		case b75:
			term.c_cflag |= B75;
			break;
		case b110:
			term.c_cflag |= B110;
			break;
		case b134:
			term.c_cflag |= B134;
			break;
		case b150:
			term.c_cflag |= B150;
			break;
		case b200:
			term.c_cflag |= B200;
			break;
		case b300:
			term.c_cflag |= B300;
			break;
		case b600:
			term.c_cflag |= B600;
			break;
		case b1200:
			term.c_cflag |= B1200;
			break;
		case b2400:
			term.c_cflag |= B2400;
			break;
		case b4800:
			term.c_cflag |= B4800;
			break;
		case b9600:
			term.c_cflag |= B9600;
			break;
		case b19200:
			term.c_cflag |= B19200;
			break;
		case b38400:
			term.c_cflag |= B38400;
			break;
		case b57600:
			term.c_cflag |= B57600;
			break;
		case b115200:
			term.c_cflag |= B115200;
			break;
		default:
			throw SerialRS232Exception("[SerialRS232::SerialRS232] Incorrect baud rate");
	};

	if (ioctl (m_port, TCSETA, &term)==-1)
		throw SerialRS232Exception("[SerialRS232::SerialRS232] Error when calling ioctl (SET)");


	if (buflen <= 0)
		throw SerialRS232Exception("[SerialRS232::SerialRS232] Buffer length must be greater than zero");

	m_dev = new char[strlen(dev) + 1];
	strcpy(m_dev, dev);
	
	m_baudrate = baudrate;
	
	m_parity = parity;
	
	m_databitsnum = databitsnum;
	
	m_stopbitsnum = stopbitsnum;
	
	m_buflen = buflen;
	m_buf = new char[m_buflen];

	m_timeout = timeout;

	m_millisecs = millisecs;
}

SerialRS232::~SerialRS232() throw (SerialRS232Exception &)
{
	delete [] m_buf;
	delete [] m_dev;
	if (close(m_port) != 0)
		throw SerialRS232Exception("[SerialRS232::~SerialRS232] Error closing");
}

char * SerialRS232::read_RS232() throw (SerialRS232Exception &)
{
	struct tms process_time;
	long read_time;
	char read_char = -111; // absurd value, might be STX (decimal 2)
	int read_bytes = 0;
	unsigned int i = 0;

	if (m_timeout > 0)
		read_time = times(&process_time) + m_timeout + 1;
	else
		read_time = -1;

	struct termio term;

	if (ioctl(m_port, TCGETA, &term) == -1)
		throw SerialRS232Exception("[SerialRS232::read_RS232] Error when calling ioctl (GET)");

	term.c_cc[VMIN] = 0;
	term.c_cc[VTIME] = (m_timeout + 9)/10;

	if (ioctl (m_port, TCSETA, &term) == -1)
		throw SerialRS232Exception("[SerialRS232::read_RS232] Error when calling ioctl (SET)");

	while((i < (m_buflen - 1)) )
	{

		/* Check if we have something to read from the buffer */
		if( status_RS232() == 0 ) {
			break;
		}

		read_bytes = read(m_port, &read_char, 1);
		if (read_bytes == -1)
			throw SerialRS232Exception("[SerialRS232::read_RS232] Error reading");
		if ((read_time > 0) && (read_time - times(&process_time)) <= 0)
			throw SerialRS232Exception("[SerialRS232::read_RS232] Timeout reading");
		if (read_bytes == 1)
		{
			*(m_buf + i) = read_char;
			i++;
		}
	}

	m_buf[i] = '\0';
	return m_buf;
}

void SerialRS232::write_RS232(const char * s, int length) throw (SerialRS232Exception &)
{

	if ((unsigned int)length > (m_buflen - 1))
		throw SerialRS232Exception("[SerialRS232::write_RS232] Too large string");

	if (write(m_port, s, length) != (int)(length)) {
		throw SerialRS232Exception("[SerialRS232::write_RS232] Error writing");
	}

}

void SerialRS232::flush_RS232() throw (SerialRS232Exception &)
{
	if (ioctl(m_port, TCFLSH, 0) == -1)
		throw SerialRS232Exception("[SerialRS232::flush_RS232] Error flushing");
}

int SerialRS232::status_RS232() throw (SerialRS232Exception &) {
	fd_set fds;
	struct timeval tv;
	int retval;

	FD_ZERO(&fds);
	FD_SET(m_port,&fds);
	tv.tv_sec = 0;
	tv.tv_usec = m_millisecs*1000;

	retval = select(m_port+1,&fds,NULL,NULL,&tv);

	if( retval == -1 )
		throw SerialRS232Exception("[SerialRS232::status_RS232] Error on select()");

	return retval;
}

SerialRS232::SerialRS232Exception::SerialRS232Exception(const char * ex) : exception()
{
	strncpy(exception_msg, ex, 99);
}
