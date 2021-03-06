#include "AmericanPlug.h"
#include "EuropeanPlug.h"
#include "EuropeanPlugAdapter.h"
#include "WallOutlet.h"

namespace Adapter {
	void Run() {
		AmericanPlug american;
		EuropeanPlug european;
		EuropeanPlugAdapter europe_adapter(american);

		WallOutlet outlet;

		//outlet.PowerDevice( american ); // Does not compile
		outlet.PowerDevice(european);
		outlet.PowerDevice(europe_adapter);
	}
}