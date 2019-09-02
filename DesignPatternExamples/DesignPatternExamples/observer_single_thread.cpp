#include <iostream>
#include <set>
#include <string>

namespace ObserverSingleThread {

	class IObserver {
	public:
		virtual void Notify() = 0;
	};

	class IObservable {
	public:
		virtual void RegisterObserver(IObserver& observer) = 0;
		virtual void UnregisterObserver(IObserver& observer) = 0;
	};

	class Alarm : public IObservable {
	public:
		Alarm() = default;
		virtual ~Alarm() = default;
		virtual void RegisterObserver(IObserver& observer) override {
			observers_.emplace(&observer);
		}
		virtual void UnregisterObserver(IObserver& observer) override {
			if (observers_.find(&observer) != observers_.end()) {
				observers_.erase(&observer);
			}
		}
		void ActivateAlarm() {
			for (auto observer : observers_) {
				observer->Notify();
			}
		}

	private:
		std::set<IObserver*> observers_;
	};

	class Speaker : public IObserver {
	public:
		Speaker(const std::string& name) : name_(name) {};
		virtual ~Speaker() = default;
		virtual void Notify() override {
			std::cout << "ALARM ACTIVE for " << name_ << std::endl;
		}

	private:
		std::string name_;
	};

	void Run() {
		Speaker spkr1("Speaker 1");
		Speaker spkr2("Speaker 2");
		Speaker spkr3("Speaker 3");
	
		Alarm alarm;
		std::cout << "Registering speaker 1..." << std::endl;
		alarm.RegisterObserver(spkr1);
		std::cout << "Registering speaker 2..." << std::endl;
		alarm.RegisterObserver(spkr2);
		std::cout << "Activating alarm..." << std::endl;
		alarm.ActivateAlarm();
		std::cout << "Unregistering speaker 2..." << std::endl;
		alarm.UnregisterObserver(spkr2);
		std::cout << "Registering speaker 3..." << std::endl;
		alarm.RegisterObserver(spkr3);
		std::cout << "Activating alarm..." << std::endl;
		alarm.ActivateAlarm();
	}
}