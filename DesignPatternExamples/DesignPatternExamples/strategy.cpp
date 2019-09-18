#include <iostream>
#include <memory>

namespace Strategy {
	class SwimStrategy {
	public:
		virtual void Swim() = 0;
	};

	class BareFeet : public SwimStrategy {
	public:
		virtual void Swim() override {
			std::cout << "Swimming with bare feet." << std::endl;
		}
	};

	class ScubaFins : public SwimStrategy {
	public:
		virtual void Swim() override {
			std::cout << "Getting faster with some sweet Scuba gear." << std::endl;
		}
	};

	class WaterJets : public SwimStrategy {
		virtual void Swim() override {
			std::cout << "Dang son, is there a speed limit in the ocean?" << std::endl;
		}
	};

	class Swimmer {
	public:
		Swimmer( std::unique_ptr<SwimStrategy> swim_strat ) :
			swim_strat_( std::move( swim_strat ) ) {};

		void Swim() {
			swim_strat_->Swim();
		}

	private:
		std::unique_ptr<SwimStrategy> swim_strat_;
	};

	void Run() {
		Swimmer me( std::make_unique<BareFeet>() );
		Swimmer someone_with_talent( std::make_unique<ScubaFins>() );
		Swimmer michael_phelps( std::make_unique<WaterJets>() );

		me.Swim();
		someone_with_talent.Swim();
		michael_phelps.Swim();
	}
}