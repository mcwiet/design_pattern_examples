#pragma once

#include "IEuropeanPlug.h"
#include <iostream>

class WallOutlet {
public:
	WallOutlet() = default;
	virtual ~WallOutlet() = default;

	void PowerDevice( IEuropeanPlug& plug ) {
		plug.EuropeanPlugIn();
		std::cout << "Plugged into a european outlet." << std::endl;
	}
};