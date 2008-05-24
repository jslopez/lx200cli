/******************************************************************************
 * OAN - Observatorio Astronómico Nacional
 * (c) OAN, 2004
 *
 * This code is under GNU General Public Licence (GPL).
 *
 * serialport_rs232.h
 *
 * who       when        what
 * --------  ----------  ----------------------------------------------
 * rbolano   2004/03/14  created
 * rtobar    2008/04/01  handling the end of the read with select()
 */

#ifndef _SERIALPORT_RS232_H_
#define _SERIALPORT_RS232_H_

#include <exception>
using namespace std;

class SerialRS232
{
public:
	/**
	 * Exception class that handles all the serial port exceptions.
	 */
	class SerialRS232Exception : public exception
	{
	private:
		char exception_msg[100];
	public:
		/**
		 * Exception constructor.
		 * @param exception message (char *).
		 */
		SerialRS232Exception(const char * ex);

		/**
		 * @returns message from the exception thrown by the serial
		 * port.
		 */
		const char * what() {return exception_msg;}
	};

	/**
	 * Supported baud rates for the serial port.
	 */
	enum baudrates {b50, b75, b110, b134, b150, b200, b300, b600, b1200,
				b2400, b4800, b9600, b19200, b38400, b57600,
				b115200};
	
	/**
	 * Supported parities for the serial port.
	 */
	enum parities {noparity, odd, even};

	/**
	 * Supported number of data bits.
	 */
	enum databits {data5, data6, data7, data8};

	/**
	 * Supported number of stop bits.
	 */
	enum stopbits {stop1, stop2};
	
	/**
	 * Constructor.  Opens the serial port for a communication
	 * according to the RS232 protocol.
	 * @param dev device to be opened (char *).
	 * @param baudrate input-output baud rate (enum). Defaults
	 *        to b9600.
	 * @param parity specifies if parity is used or not. If used, parity 
	 *        must be odd or even (enum). Defaults to noparity.
	 * @param databitsnum number of data bits per byte. Must be data5, 
	 *        data6, data7 or data8 (enum). Defaults to data8.
	 * @param stopbitsnum number of stop bits. Must be stop1 or stop2
	 *        (enum). Defaults to stop1.
	 * @param termc frame termination character (int). Defaults to 10 ('\n').
	 *        If termc < 0 this condition is ignored.
	 * @param buflen maximum number of characters to be read (unsigned int).
	 *        Defaults to 1024.
	 * @param timeout maximum time in centisecs for a reading operation 
	 *        (int). Defaults to 300. If tout <= 0 this condition is ignored.
	 */
	SerialRS232(const char * dev,
			const long & millisecs = 50,
			const baudrates & baudrate = b9600,
			const parities & parity = noparity,
			const databits & databitsnum = data8,
			const stopbits & stopbitsnum = stop1,
			const unsigned int & buflen = 1024,
			const int & timeout = 900)
			throw (SerialRS232Exception &);

	/**
	 * Destructor.
	 */
	~SerialRS232() throw (SerialRS232Exception &);

	/**
	 * @returns buffer read from the port as a char*
	 */
	char * read_RS232() throw (SerialRS232Exception &);
	
	/**
	 * Writes a buffer to the port.
	 * @param s buffer to be written (char *)
	 * @param l lenght of the buffer to be written (int)
	 */
	void write_RS232(const char * s, int l) throw (SerialRS232Exception &);
	
	/**
	 * Flushes the serial port.
	 */
	void flush_RS232() throw (SerialRS232Exception &);

private:

	baudrates m_baudrate;
	parities m_parity;
	databits m_databitsnum;
	stopbits m_stopbitsnum;
	unsigned int m_buflen;
	int m_port;
	char * m_dev;
	char * m_buf;
	int m_timeout;
	long m_millisecs;

	/**
	 * Checks if the buffer has something to read.
	 */
	int status_RS232() throw (SerialRS232Exception &);
};

#endif

