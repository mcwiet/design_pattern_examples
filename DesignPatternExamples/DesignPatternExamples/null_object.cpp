#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <thread>

namespace NullObject {
	class TimeModel {
	public:
		virtual std::chrono::milliseconds GetDelay() = 0;
		virtual void Print() {
			std::cout << ".";
		}
	};

	class TimeRunner {
	public:
		TimeRunner(std::unique_ptr<TimeModel> default_time) :
			time_(std::move(default_time)),
			thread_(&TimeRunner::Run, this) {}
		void ChangeTime(std::unique_ptr<TimeModel> time) {
			std::cout << "change enter" << std::endl;
			mutex_.lock();
			{
				time_ = std::move(time);
				mutex_.unlock();
			}
			std::cout << "change exit" << std::endl;
		}

	private:
		void Run() {
			std::chrono::milliseconds delay;
			while (true) {
				mutex_.lock();
				{
					delay = time_->GetDelay();
					mutex_.unlock();
				}
				std::this_thread::sleep_for(delay);
				mutex_.lock();
				{
					time_->Print();
					mutex_.unlock();
				}
			}
		}

		std::unique_ptr<TimeModel> time_ = nullptr;
		std::thread thread_;
		std::mutex mutex_;
	};

	class NormalTime : public TimeModel {
	public:
		virtual std::chrono::milliseconds GetDelay() {
			return std::chrono::milliseconds(1000);
		}
	};

	class DoubleTime : public TimeModel {
	public:
		virtual std::chrono::milliseconds GetDelay() {
			return std::chrono::milliseconds(500);
		}
	};

	class NullTime : public TimeModel {
	public:
		virtual std::chrono::milliseconds GetDelay() {
			return std::chrono::milliseconds(0);
		}
		virtual void Print() override {
			// Do nothing
		}
	};

	void Run() {
		std::cout << "Select time" << std::endl
			<< "0 = Null" << std::endl
			<< "1 = Normal" << std::endl
			<< "2 = Double" << std::endl;

		std::string input;
		TimeRunner runner(std::make_unique<NullTime>());

		while (true) {
			std::getline(std::cin, input);
			if (input == "0")
				runner.ChangeTime(std::make_unique<NullTime>());
			else if (input == "1")
				runner.ChangeTime(std::make_unique<NormalTime>());
			else if (input == "2")
				runner.ChangeTime(std::make_unique<DoubleTime>());
		}
	}
}