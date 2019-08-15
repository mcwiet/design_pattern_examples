#include <iostream>
#include <memory>
#include <string>

class Receiver {
public:
	Receiver() = default;
	virtual ~Receiver() = default;

	void Say( std::string& msg ) {
		std::cout << msg << std::endl;
	}
};

class ICommand {
public:
	virtual void Execute() = 0;
};

class MikeCompliment1 : public ICommand {
public:
	MikeCompliment1() :
		message_( "Mike is the best!" ) {};
	virtual ~MikeCompliment1() = default;

	virtual void Execute() override {
		receiver_.Say( message_ );
	}

private:
	Receiver receiver_;
	std::string message_;
};

class MikeCompliment2 : public ICommand {
public:
	MikeCompliment2() :
		message_( "Mike is amazing!" ) {};

	virtual ~MikeCompliment2() = default;

	virtual void Execute() override {
		receiver_.Say( message_ );
	}

private:
	Receiver receiver_;
	std::string message_;
};

class MikeInsult2834739879570 : public ICommand {
public:
	MikeInsult2834739879570() :
		message_( "We don't need to type the insult out again.... you get the point, right?" ) {};

	virtual ~MikeInsult2834739879570() = default;

	virtual void Execute() override {
		receiver_.Say( message_ );
	}

private:
	Receiver receiver_;
	std::string message_;
};

class Invoker {
public:
	Invoker( std::unique_ptr<ICommand> cmd_a, std::unique_ptr<ICommand> cmd_b, std::unique_ptr<ICommand> cmd_c ) :
		cmd_a_( std::move( cmd_a ) ),
		cmd_b_( std::move( cmd_b ) ),
		cmd_c_( std::move( cmd_c ) ) {};

	virtual ~Invoker() = default;

	void Invoke( std::string& cmd ) {
		if (cmd == "a") {
			cmd_a_->Execute();
		}
		else if (cmd == "b") {
			cmd_b_->Execute();
		}
		else if (cmd == "c") {
			cmd_c_->Execute();
		}
		else {
			std::cout << "Invalid command." << std::endl;
		}
	}

private:
	std::unique_ptr<ICommand> cmd_a_;
	std::unique_ptr<ICommand> cmd_b_;
	std::unique_ptr<ICommand> cmd_c_;
};

//int main() {
//	std::string input;
//
//	auto cmd1 = std::make_unique<MikeCompliment1>();
//	auto cmd2 = std::make_unique<MikeCompliment2>();
//	auto cmd3 = std::make_unique<MikeInsult2834739879570>();
//
//	Invoker invoker( std::move( cmd1 ), std::move( cmd2 ), std::move( cmd3 ) );
//
//	while (1) {
//		std::cout << "Enter a command: ";
//		getline( std::cin, input );
//		invoker.Invoke( input );
//	}
//
//	return 0;
//}