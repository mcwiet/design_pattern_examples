#include "adapter.cpp"
#include "command_with_undo.cpp"
#include "command_without_undo.cpp"
#include "crtp.cpp"
#include "decorator.cpp"
#include "facade.cpp"
#include "observer_multi_thread.cpp"
#include "observer_single_thread.cpp"
#include "proxy.cpp"
#include "singleton.cpp"
#include "strategy.cpp"
#include "template.cpp"

int main() {
	//Adapter::Run();
	//CommandWithUndo::Run();
	//CommandWithoutUndo::Run();
	//CRTP::Run();
	Decorator::Run();
	//Facade::Run();
	//ObserverMultiThread::Run();
	//ObserverSingleThread::Run();
	//Template::Run();
	//Singleton::Run();
	//Strategy::Run();
	//Proxy::Run();

	return 0;
}