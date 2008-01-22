/** 
 * \file Communication.h
 * Headers to implement the communication with the Meade LX200 GPS telescope.
 *
 * \author Joao Lopez <jslopez@csrg.inf.utfsm.cl>
 */

#include <SerialRS232.h>

using namespace std;

/**
 * Class that handles comunication.
 */
class Communication{

	private:
		SerialRS232 *sp;

	public:
		/** 
		 * Constructor 
		 * @param deviceName The serial port device
		 */
		Communication(char *deviceName);

		/** Destructor */
		~Communication();

		/** Initialize telescope command */
		void initializeTelescope();

		/** Get Telescope Altitude */
		void getAltitude();

		/** Get Telescope Declination */
		void getDeclination();

		/** Get Telescope RA */
		void getRA();

		/** Get the Sidereal Time */
		void getSiderealTime();

		/** Get tracking rate */
		void getTrackingRate();

		/** Get Telescope Azimuth */
		void getAzimuth();

};
