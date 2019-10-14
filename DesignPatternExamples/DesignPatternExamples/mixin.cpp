#include <iostream>

namespace Mixin {
	template <typename T>
	class Value {
	public:
		typedef T value_type_;
		T Get() { return value_; }
		void Set(T val) { value_ = val; }
	protected:
		T value_;
	};

	template <typename BASE, typename T = typename BASE::value_type_>
	class Undoable : public BASE {
	public:
		void Set(T val) { prev_val_ = BASE::Get(); BASE::Set(val); }
		void Undo() { BASE::Set(prev_val_); }
	private:
		T prev_val_;
	};

	template <typename BASE, typename T = typename BASE::value_type_>
	class Redoable : public BASE {
	public:
		void Set(T val) { next_val_ = val; BASE::Set(val); }
		void Redo() { BASE::Set(next_val_); }
	private:
		T next_val_;
	};

	typedef Redoable<Undoable<Value<int>>> IntWithMemory;

	void Run() {
		IntWithMemory x;
		x.Set(10);
		std::cout << "Set x to 10. Current value is: " << x.Get() << std::endl;
		x.Set(20);
		std::cout << "Set x to 20. Current value is: " << x.Get() << std::endl;
		x.Undo();
		std::cout << "Undo. Current value is: " << x.Get() << std::endl;
		x.Redo();
		std::cout << "Redo. Current value is: " << x.Get() << std::endl;
	}
}