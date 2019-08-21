#pragma once

#include "IEuropeanPlug.h"
#include <iostream>

class EuropeanPlug : public IEuropeanPlug {
public:
	EuropeanPlug() = default;
	virtual ~EuropeanPlug() = default;

	virtual void EuropeanPlugIn() override {
		std::cout << "Plugging in *tea spills, krumpets crumble*." << std::endl;
	}
};