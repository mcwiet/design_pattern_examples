#include <iostream>

namespace Facade {
	class Coding {
	public:
		void Code() {
			std::cout << "Coding for a few hours..." << std::endl;
		}
	};

	class Lunch {
	public:
		void GoEatLunch() {
			std::cout << "Going to eat lunch!" << std::endl;
		}
	};

	class Bathroom {
	public:
		void UseBathroom() {
			std::cout << "Using the bathroom." << std::endl;
		}
	};

	class Transportation {
	public:
		void GoToWork() {
			std::cout << "Going to work." << std::endl;
		}
		void GoHome() {
			std::cout << "Leaving work." << std::endl;
		}
	};

	class WorkDayFacade {
	public:
		void DoWorkToday() {
			trasport_.GoToWork();
			code_.Code();
			bathroom_.UseBathroom();
			lunch_.GoEatLunch();
			code_.Code();
			bathroom_.UseBathroom();
			code_.Code();
			trasport_.GoHome();
		}

	private:
		Transportation trasport_;
		Bathroom bathroom_;
		Lunch lunch_;
		Coding code_;
	};

	void Run() {
		WorkDayFacade work_day;
		std::cout << "It's a work day! Executing my work routine..." << std::endl;
		work_day.DoWorkToday();
	}
}