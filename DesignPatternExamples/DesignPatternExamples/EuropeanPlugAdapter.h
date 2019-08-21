#pragma once

#include "IEuropeanPlug.h"
#include "AmericanPlug.h"

class EuropeanPlugAdapter : public IEuropeanPlug {
public:
	EuropeanPlugAdapter( AmericanPlug& plug ) : adapted_plug_( plug ) {};
	virtual ~EuropeanPlugAdapter() = default;

	virtual void EuropeanPlugIn() override {
		adapted_plug_.PlugIn();
	}

private:
	AmericanPlug& adapted_plug_;
};