#include <iostream>
#include <set>
#include <string>
#include <thread>
#include <chrono>
#include <mutex>

class IRunnable {
public:
	virtual void Run() = 0;
};

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
	Alarm() :is_active_(false) {};
	virtual ~Alarm() = default;
	virtual void RegisterObserver(IObserver& observer) override {
		observers_.emplace(&observer);
	}
	virtual void UnregisterObserver(IObserver& observer) override {
		if (observers_.find(&observer) != observers_.end()) {
			observers_.erase(&observer);
		}
	}
	void Activate() {
		SetIsActive(true);
	}
	void Deactivate() {
		SetIsActive(false);
	}
	bool IsActive() {
		return is_active_;
	}

private:
	void SetIsActive(bool is_active) {
		is_active_ = is_active;
		for (auto observer : observers_) {
			observer->Notify();
		}
	}

	std::set<IObserver*> observers_;
	bool is_active_;
};

class ThreadSafeOutput {
public:
	friend std::ostream& operator<<(std::ostream& os, const std::string& str) {
		mutex_.lock();
		os << str;
	}
private:
	std::mutex mutex_;
};

class Speaker : public IObserver, public IRunnable {
public:
	Speaker(const std::string& name, Alarm& alarm, ThreadSafeOutput& out) :
		out_(out),
		is_playing_(false),
		alarm_(alarm),
		name_(name),
		thread_(&Speaker::Run, this) {};
	virtual ~Speaker() {
		thread_.join();
	}
	virtual void Notify() override {
		is_playing_ = alarm_.IsActive();
	}
	virtual void Run() override {
		std::this_thread::sleep_for(std::chrono::seconds(5));
		out_ << name_ << " active = " << is_playing_ << std::endl;
	}

private:
	ThreadSafeOutput& out_;
	bool is_playing_;
	Alarm& alarm_;
	std::string name_;
	std::thread thread_;

};

int main() {
	Alarm alarm;
	Speaker spkr1("Speaker 1", alarm);
	Speaker spkr2("Speaker 2", alarm);
	Speaker spkr3("Speaker 3", alarm);

	std::string input;

	while (input != "exit") {
		std::getline(std::cin, input);

		if (input == "register speaker 1") {
			alarm.RegisterObserver(spkr1);
		}
		else if (input == "register speaker 2") {
			alarm.RegisterObserver(spkr2);
		}
		else if (input == "register speaker 3") {
			alarm.RegisterObserver(spkr3);
		}
		else if (input == "unregister speaker 1") {
			alarm.UnregisterObserver(spkr1);
		}
		else if (input == "unregister speaker 2") {
			alarm.UnregisterObserver(spkr2);
		}
		else if (input == "unregister speaker 3") {
			alarm.UnregisterObserver(spkr3);
		}
		else if (input == "activate") {
			alarm.Activate();
		}
		else if (input == "deactivate") {
			alarm.Deactivate();
		}
	}

	return 0;
}