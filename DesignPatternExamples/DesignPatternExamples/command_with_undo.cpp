#include <iostream>
#include <memory>
#include <string>
#include <stack>

namespace CommandWithUndo {

	class Receiver {
	public:
		Receiver() = default;
		virtual ~Receiver() = default;

		void Say(std::string& msg) {
			std::cout << msg << std::endl;
		}
	};

	class ICommand {
	public:
		virtual void Execute() = 0;
		virtual void UnExecute() = 0;
	};

	class MikeCompliment1 : public ICommand {
	public:
		MikeCompliment1() :
			message_("Mike is the best!"),
			undo_message_("Mike is not the best :(") {};
		virtual ~MikeCompliment1() = default;

		virtual void Execute() override {
			receiver_.Say(message_);
		}

		virtual void UnExecute() override {
			receiver_.Say(undo_message_);
		}

	private:
		Receiver receiver_;
		std::string message_;
		std::string undo_message_;
	};

	class MikeCompliment2 : public ICommand {
	public:
		MikeCompliment2() :
			message_("Mike is amazing!"),
			undo_message_("Mike is not amazing :(") {};

		virtual ~MikeCompliment2() = default;

		virtual void Execute() override {
			receiver_.Say(message_);
		}

		virtual void UnExecute() override {
			receiver_.Say(undo_message_);
		}

	private:
		Receiver receiver_;
		std::string message_;
		std::string undo_message_;
	};

	class MikeInsult2834739879570 : public ICommand {
	public:
		MikeInsult2834739879570() :
			message_("We don't need to type the insult out again.... you get the point, right?"),
			undo_message_("Undoing that insult we weren't gonna talk about anymore") {};

		virtual ~MikeInsult2834739879570() = default;

		virtual void Execute() override {
			receiver_.Say(message_);
		}

		virtual void UnExecute() override {
			receiver_.Say(undo_message_);
		}

	private:
		Receiver receiver_;
		std::string message_;
		std::string undo_message_;
	};

	class Invoker {
	public:
		Invoker(std::unique_ptr<ICommand> cmd_a, std::unique_ptr<ICommand> cmd_b, std::unique_ptr<ICommand> cmd_c) :
			cmd_a_(std::move(cmd_a)),
			cmd_b_(std::move(cmd_b)),
			cmd_c_(std::move(cmd_c)) {};

		virtual ~Invoker() = default;

		void Invoke(std::string& cmd) {
			if (cmd == "a") {
				cmd_a_->Execute();
				cmds_.push(cmd_a_.get());
			}
			else if (cmd == "b") {
				cmd_b_->Execute();
				cmds_.push(cmd_b_.get());
			}
			else if (cmd == "c") {
				cmd_c_->Execute();
				cmds_.push(cmd_c_.get());
			}
			else if (cmd == "undo") {
				UndoAll();
			}
			else {
				std::cout << "Invalid command." << std::endl;
			}
		}

		void UndoAll() {
			while (!cmds_.empty()) {
				auto cmd = cmds_.top();
				cmd->UnExecute();
				cmds_.pop();
			}
		}

	private:
		std::unique_ptr<ICommand> cmd_a_;
		std::unique_ptr<ICommand> cmd_b_;
		std::unique_ptr<ICommand> cmd_c_;
		std::stack<ICommand*> cmds_;
	};

	void Run() {
		std::string input;
	
		auto cmd1 = std::make_unique<MikeCompliment1>();
		auto cmd2 = std::make_unique<MikeCompliment2>();
		auto cmd3 = std::make_unique<MikeInsult2834739879570>();
	
		Invoker invoker( std::move( cmd1 ), std::move( cmd2 ), std::move( cmd3 ) );
	
		while (1) {
			std::cout << "Enter a command: ";
			getline( std::cin, input );
			invoker.Invoke( input );
		}
	}
}