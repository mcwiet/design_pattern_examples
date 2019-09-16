#include <iostream>
#include <memory>
#include <thread>

namespace Proxy {
	struct ICommon {
		virtual void Foo() = 0;
	};

	struct SlowToConstruct : public ICommon {
		SlowToConstruct() {
			std::cout << "Starting slow construction..." << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(2));
			std::cout << "Finished slow construction!" << std::endl;
		}
		virtual ~SlowToConstruct() = default;
		virtual void Foo() override {
			std::cout << "Retrieving data that was calculated during construction." << std::endl;
		}
	};

	struct Proxy : public ICommon {
		Proxy() = default;
		virtual ~Proxy() = default;
		virtual void Foo() override {
			if (slow_ == nullptr){
				// This is part Proxy / part Lazy Init
				slow_ = std::make_unique<SlowToConstruct>();
			}
			std::cout << "Performing function!" << std::endl;
		}

	private:
		std::unique_ptr<SlowToConstruct> slow_;
	};


	void Run() {
		std::cout << "Creating my proxy..." << std::endl;
		Proxy proxy;
		std::cout << "Pretend to do a bunch of stuff without actually using the object yet." << std::endl;
		std::cout << "Need to use the object, calling into proxy..." << std::endl;
		proxy.Foo();
		std::cout << "Need to use the object a second time (should not be slow this time)..." << std::endl;
		proxy.Foo();
	}
}