/** 
 * \file Communication.h
 * Headers to implement the communication with the Meade LX200 GPS telescope.
 *
 * \author Joao Lopez <jslopez@csrg.inf.utfsm.cl>
 */

#include <SerialRS232.h>
#include <conversions.h>

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
		 * Set AltAz alignment mode. 
		 * @param deviceName The serial port device
		 */
		Communication(char *deviceName);

		/** Destructor */
		~Communication();

		/** Get Telescope Altitude */
		double getAltitude();

		/** Get Telescope Azimuth */
		double getAzimuth();

		/** 
		 * Get the Sidereal Time 
		 * @param *stime Array for time values (HH:MM:SS)
		 */
		void getSiderealTime(int *stime);
	
		/**
		 * Slew in received direction
		 * @param direction n(north), s(south), w(west), e(east)
		 * @returns true for right format direction and false for wrong
		 */
		bool slew(char direction);

		/** Halt all current slewing */
		void haltSlewing();
};
