#include <SerialRS232.h>

using namespace std;

class Communication{

	private:
		SerialRS232 *sp;

	public:
		Communication(char *deviceName);
		~Communication();

	void initializeTelescope()
	void getAltitude()
	void getDeclination()
	void getRA()
	void getSiderealTime()
	void getTrackingRate()
	void getAzimuth()

}
