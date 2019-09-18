#include <iostream>
#include <vector>

namespace Singleton {
	class TheSingleton {
	public:
		TheSingleton( const TheSingleton& ) = delete;
		TheSingleton& operator=( const TheSingleton& ) = delete;
		TheSingleton( TheSingleton&& ) = delete;
		TheSingleton& operator=( TheSingleton&& ) = delete;

		static TheSingleton& GetInstance() {
			static TheSingleton instance;
			return instance;
		}

		int GetData() {
			return data_;
		}

		void SetData( int data ) {
			data_ = data;
		}

	private:
		TheSingleton() : data_( 0 ) {};
		int data_;
	};

	void Run() {
		std::vector<std::reference_wrapper<TheSingleton>> instances;
		instances.emplace_back( TheSingleton::GetInstance() );
		instances.emplace_back( TheSingleton::GetInstance() );
		instances.emplace_back( TheSingleton::GetInstance() );

		std::cout << "Initial values of all instances:" << std::endl;
		for (TheSingleton& inst : instances) {
			std::cout << inst.GetData() << std::endl;
		}
		std::cout << std::endl;

		std::cout << "Modifying value of instance 0:" << std::endl;
		instances.at( 0 ).get().SetData( 20 );

		std::cout << "New values of all instances:" << std::endl;
		for (TheSingleton& inst : instances) {
			std::cout << inst.GetData() << std::endl;
		}
		std::cout << std::endl;

		std::cout << "Modifying value of instance 2:" << std::endl;
		instances.at( 2 ).get().SetData( 15 );

		std::cout << "New values of all instances:" << std::endl;
		for (TheSingleton& inst : instances) {
			std::cout << inst.GetData() << std::endl;
		}
		std::cout << std::endl;
	}
}