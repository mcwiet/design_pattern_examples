#include <iostream>
#include <string>
#include <memory>

namespace Decorator {
	class ICustomShirt {
	public:
		virtual void Print() = 0;
	};

	class BlueShirt : public ICustomShirt {
	public:
		virtual void Print() override {
			std::cout << "Printing blue shirt..." << std::endl;
		}
	};

	class WhiteShirt : public ICustomShirt {
		virtual void Print() override {
			std::cout << "Printing white shirt..." << std::endl;
		}
	};

	class CustomShirtDecorator : public ICustomShirt {
	public:
		CustomShirtDecorator( std::shared_ptr<ICustomShirt> shirt ) :shirt_( shirt ) {};
		virtual void Print() override = 0;
	protected:
		std::shared_ptr<ICustomShirt> shirt_;
	};

	class GoldStars : public CustomShirtDecorator {
	public:
		GoldStars( std::shared_ptr<ICustomShirt> shirt ) : CustomShirtDecorator( shirt ) {};
		virtual void Print() override {
			shirt_->Print();
			std::cout << "  with gold stars..." << std::endl;
		}
	};

	class PhiladelphiaEaglesLogo : public CustomShirtDecorator {
	public:
		PhiladelphiaEaglesLogo( std::shared_ptr<ICustomShirt> shirt ) : CustomShirtDecorator( shirt ) {};
		virtual void Print() override {
			shirt_->Print();
			std::cout << "  with Philadelphia Eagles logo..." << std::endl;
		}
	};

	class FakeBowTie : public CustomShirtDecorator {
	public:
		FakeBowTie( std::shared_ptr<ICustomShirt> shirt ) : CustomShirtDecorator( shirt ) {};
		virtual void Print() override {
			shirt_->Print();
			std::cout << "  with fake bow tie..." << std::endl;
		}
	};

	class SupermanSymbol : public CustomShirtDecorator {
	public:
		SupermanSymbol( std::shared_ptr<ICustomShirt> shirt ) : CustomShirtDecorator( shirt ) {};
		virtual void Print() override {
			shirt_->Print();
			std::cout << "  with Superman 'S'..." << std::endl;
		}
	};

	void Run() {
		auto superman_shirt = std::make_shared<SupermanSymbol>(
			std::make_shared<BlueShirt>() );

		auto eagles_shirt = std::make_shared<PhiladelphiaEaglesLogo>(
			std::make_shared<WhiteShirt>() );

		auto drunken_order = std::make_shared<GoldStars>(
			std::make_shared<PhiladelphiaEaglesLogo>(
				std::make_shared<FakeBowTie>(
					std::make_shared<BlueShirt>() ) ) );

		superman_shirt->Print();
		eagles_shirt->Print();
		drunken_order->Print();
	}
}