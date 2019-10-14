#include "adapter.cpp"
#include "bridge.cpp"
#include "command_with_undo.cpp"
#include "command_without_undo.cpp"
#include "composite.cpp"
#include "crtp.cpp"
#include "decorator.cpp"
#include "facade.cpp"
#include "factory.cpp"
#include "factory_abstract.cpp"
#include "iterator.cpp"
#include "mixin.cpp"
#include "null_object.cpp"
#include "observer_multi_thread.cpp"
#include "observer_single_thread.cpp"
#include "proxy.cpp"
#include "singleton.cpp"
#include "state.cpp"
#include "strategy.cpp"
#include "template.cpp"

int main() {
	//Adapter::Run();
	//Bridge::Run();
	//CommandWithUndo::Run();
	//CommandWithoutUndo::Run();
	//Composite::Run();
	//CRTP::Run();
	//Decorator::Run();
	//Facade::Run();
	//Factory::Run();
	FactoryAbstract::Run();
	//Iterator::Run();
	Mixin::Run();
	//NullObject::Run();
	//ObserverMultiThread::Run();
	//ObserverSingleThread::Run();
	//Template::Run();
	//Singleton::Run();
	//State::Run();
	//Strategy::Run();
	//Proxy::Run();

	return 0;
}