#include <iostream>
#include <string>
#include <memory>
namespace State {
	// This templating portion isn't part of the state pattern. I want my states to return
	// new states after an action has been executed but I don't want to duplicate code with having
	// two interfaces (one for the laptop, one for the laptop states) that must be updated
	// simultaneously. This method should allow me to have a single interface but I can specify
	// the return type based on the context of where it's being implemented.
	template <typename T>
	class ILaptop {
	public:
		virtual ~ILaptop() = default;
		virtual T TurnOn() = 0;
		virtual T TurnOff() = 0;
		virtual T PlayGames() = 0;
		virtual T DoWork() = 0;
	};

	static inline void Message(const std::string& msg) { std::cout << msg << std::endl; }

	struct LaptopState : public ILaptop<std::unique_ptr<LaptopState>> {
		virtual ~LaptopState() = default;
	};

	struct Laptop : public ILaptop<void> {
		Laptop(std::unique_ptr<LaptopState> init_state) :
			state_(std::move(init_state)) {};
		virtual ~Laptop() = default;
		virtual void TurnOn() override {
			state_ = std::move(state_->TurnOn());
		}
		virtual void TurnOff() override {
			state_ = std::move(state_->TurnOff());
		}
		virtual void PlayGames() override {
			state_ = std::move(state_->PlayGames());
		}
		virtual void DoWork() override {
			state_ = std::move(state_->DoWork());
		}

	private:
		std::unique_ptr<LaptopState> state_;
	};

	struct IdleState : public LaptopState {
		virtual ~IdleState() = default;
		virtual std::unique_ptr<LaptopState> TurnOn();
		virtual std::unique_ptr<LaptopState> TurnOff();
		virtual std::unique_ptr<LaptopState> PlayGames();
		virtual std::unique_ptr<LaptopState> DoWork();
	};

	struct OffState : public LaptopState {
		virtual ~OffState() = default;
		virtual std::unique_ptr<LaptopState> TurnOn();
		virtual std::unique_ptr<LaptopState> TurnOff();
		virtual std::unique_ptr<LaptopState> PlayGames();
		virtual std::unique_ptr<LaptopState> DoWork();
	};

	struct PlayGamesState : public LaptopState {
		virtual ~PlayGamesState() = default;
		virtual std::unique_ptr<LaptopState> TurnOn();
		virtual std::unique_ptr<LaptopState> TurnOff();
		virtual std::unique_ptr<LaptopState> PlayGames();
		virtual std::unique_ptr<LaptopState> DoWork();
	};

	struct DoWorkState : public LaptopState {
		virtual ~DoWorkState() = default;
		virtual std::unique_ptr<LaptopState> TurnOn();
		virtual std::unique_ptr<LaptopState> TurnOff();
		virtual std::unique_ptr<LaptopState> PlayGames();
		virtual std::unique_ptr<LaptopState> DoWork();
	};

	std::unique_ptr<LaptopState> IdleState::TurnOn() {
		Message("Output: Already on.");
		return std::move(std::make_unique<IdleState>());
	}
	std::unique_ptr<LaptopState> IdleState::TurnOff() {
		Message("Output: Turning off.");
		return std::move(std::make_unique<OffState>());
	}
	std::unique_ptr<LaptopState> IdleState::PlayGames() {
		Message("Output: Switching to games.");
		return std::move(std::make_unique<PlayGamesState>());
	}
	std::unique_ptr<LaptopState> IdleState::DoWork() {
		Message("Output: Switching to work.");
		return std::move(std::make_unique<DoWorkState>());
	}

	std::unique_ptr<LaptopState> OffState::TurnOn() {
		Message("Output: Turning on.");
		return std::move(std::make_unique<IdleState>());
	}
	std::unique_ptr<LaptopState> OffState::TurnOff() {
		Message("Output: Already off.");
		return std::move(std::make_unique<OffState>());
	}
	std::unique_ptr<LaptopState> OffState::PlayGames() {
		Message("Output: Can't play games when the computer is off!");
		return std::move(std::make_unique<OffState>());
	}
	std::unique_ptr<LaptopState> OffState::DoWork() {
		Message("Output: Can't do work when the computer is off!");
		return std::move(std::make_unique<OffState>());
	}

	std::unique_ptr<LaptopState> PlayGamesState::TurnOn() {
		Message("Output: Already on, we're playing games!");
		return std::move(std::make_unique<PlayGamesState>());
	}
	std::unique_ptr<LaptopState> PlayGamesState::TurnOff() {
		Message("Output: Turning off.");
		return std::move(std::make_unique<OffState>());
	}
	std::unique_ptr<LaptopState> PlayGamesState::PlayGames() {
		Message("Output: Already playing games!");
		return std::move(std::make_unique<PlayGamesState>());
	}
	std::unique_ptr<LaptopState> PlayGamesState::DoWork() {
		Message("Output: Switching to work.");
		return std::move(std::make_unique<DoWorkState>());
	}

	std::unique_ptr<LaptopState> DoWorkState::TurnOn() {
		Message("Output: Already on, we're working!");
		return std::move(std::make_unique<DoWorkState>());
	}
	std::unique_ptr<LaptopState> DoWorkState::TurnOff() {
		Message("Output: Turning off.");
		return std::move(std::make_unique<OffState>());
	}
	std::unique_ptr<LaptopState> DoWorkState::PlayGames() {
		Message("Output: Switching to games.");
		return std::move(std::make_unique<PlayGamesState>());
	}
	std::unique_ptr<LaptopState> DoWorkState::DoWork() {
		Message("Output: Already doing work!");
		return std::move(std::make_unique<DoWorkState>());
	}

	void Run() {
		Laptop laptop(std::make_unique<OffState>());
		std::string input;
		while (true) {
			Message("Enter one of the following commands:");
			Message("1 = Turn on");
			Message("2 = Turn off");
			Message("3 = Play games");
			Message("4 = Do work");
			Message("5 = Quit");
			std::cout << "COMMAND = ";

			std::getline(std::cin, input);

			if (input == "1")
				laptop.TurnOn();
			else if (input == "2")
				laptop.TurnOff();
			else if (input == "3")
				laptop.PlayGames();
			else if (input == "4")
				laptop.DoWork();
			else if (input == "5")
				break;

			std::cout << std::endl;
		}
	}
}