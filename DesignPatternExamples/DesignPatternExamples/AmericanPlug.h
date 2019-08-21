#pragma once

#include "IAmericanPlug.h"
#include <iostream>

class AmericanPlug : public IAmericanPlug {
public:
	AmericanPlug() = default;
	virtual ~AmericanPlug() = default;

	virtual void PlugIn() override {
		std::cout << "Plugging in *Fireworks in background, eagles sore*." << std::endl;
	}
};