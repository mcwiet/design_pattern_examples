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
	virtual void RegisterObserver( IObserver& observer ) = 0;
	virtual void UnregisterObserver( IObserver& observer ) = 0;
};

class ThreadSafeLogger {
public:
	ThreadSafeLogger( std::ostream& out ) : out_( out ) {};
	virtual ~ThreadSafeLogger() = default;

	template <typename T>
	void Log( T msg ) {
		mutex_.lock();
		out_ << msg << std::endl;
		mutex_.unlock();
	}

private:
	std::ostream& out_;
	std::mutex mutex_;
};

class Alarm : public IObservable {
public:
	Alarm( ThreadSafeLogger& log ) :
		out_( log ),
		is_active_( false ) {};
	virtual ~Alarm() = default;
	virtual void RegisterObserver( IObserver& observer ) override {
		observers_.emplace( &observer );
	}
	virtual void UnregisterObserver( IObserver& observer ) override {
		if (observers_.find( &observer ) != observers_.end()) {
			observers_.erase( &observer );
		}
	}
	void Activate() {
		SetIsActive( true );
	}
	void Deactivate() {
		SetIsActive( false );
	}
	bool IsActive() {
		return is_active_;
	}

private:
	void SetIsActive( bool is_active ) {
		is_active_ = is_active;
		out_.Log( is_active ? "alarm activated" : "alarm deactivated" );
		for (auto observer : observers_) {
			observer->Notify();
		}
	}

	ThreadSafeLogger& out_;
	std::set<IObserver*> observers_;
	bool is_active_;
};

class Speaker : public IObserver, public IRunnable {
public:
	Speaker( const std::string& name, Alarm& alarm, ThreadSafeLogger& out ) :
		out_( out ),
		is_playing_( false ),
		alarm_( alarm ),
		name_( name ),
		thread_( &Speaker::Run, this ) {};
	virtual ~Speaker() {
		thread_.join();
	}
	virtual void Notify() override {
		out_.Log( name_ + " notified!" );
		is_playing_ = alarm_.IsActive();
	}
	virtual void Run() override {
		while (true) {
			if (is_playing_)
				out_.Log( name_ + ": *alarm noises*" );
			std::this_thread::sleep_for( std::chrono::seconds( 5 ) );
		}
	}

private:
	ThreadSafeLogger& out_;
	bool is_playing_;
	Alarm& alarm_;
	std::string name_;
	std::thread thread_;
};

//int main() {
//	ThreadSafeLogger log( std::cout );
//	Alarm alarm( log );
//	Speaker spkr1( "Speaker 1", alarm, log );
//	Speaker spkr2( "Speaker 2", alarm, log );
//	Speaker spkr3( "Speaker 3", alarm, log );
//
//	std::string input;
//
//	while (input != "exit") {
//		std::getline( std::cin, input );
//
//		if (input == "register speaker 1") {
//			std::cout << "yay!" << std::endl;
//			alarm.RegisterObserver( spkr1 );
//		}
//		else if (input == "register speaker 2") {
//			alarm.RegisterObserver( spkr2 );
//		}
//		else if (input == "register speaker 3") {
//			alarm.RegisterObserver( spkr3 );
//		}
//		else if (input == "unregister speaker 1") {
//			alarm.UnregisterObserver( spkr1 );
//		}
//		else if (input == "unregister speaker 2") {
//			alarm.UnregisterObserver( spkr2 );
//		}
//		else if (input == "unregister speaker 3") {
//			alarm.UnregisterObserver( spkr3 );
//		}
//		else if (input == "activate") {
//			alarm.Activate();
//		}
//		else if (input == "deactivate") {
//			alarm.Deactivate();
//		}
//	}
//
//	return 0;
//}