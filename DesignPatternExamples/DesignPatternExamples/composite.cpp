#include <iostream>
#include <string>

namespace Composite {
	class ArithmeticExpression {
	public:
		virtual ~ArithmeticExpression() = default;
		virtual double Evaluate() = 0;
		virtual std::string Print() = 0;
	};

	class NumericOperand : public ArithmeticExpression {
	public:
		NumericOperand(double val) : val_(val) {};
		virtual double Evaluate() override { return val_; }
		virtual std::string Print() override { return std::to_string(val_); }
	private:
		double val_;
	};

	class CompositeOperand : public ArithmeticExpression {
	public:
		virtual ~CompositeOperand() = default;
		CompositeOperand(ArithmeticExpression& left, ArithmeticExpression& right) : left_(left), right_(right) {};
	protected:
		ArithmeticExpression& left_;
		ArithmeticExpression& right_;
	};

	class PlusOperand : public CompositeOperand {
	public:
		PlusOperand(ArithmeticExpression& left, ArithmeticExpression& right) : CompositeOperand(left, right) {};
		virtual std::string Print() override { return ("(" + left_.Print() + "+" + right_.Print() + ")"); }
		virtual double Evaluate() override {
			return (left_.Evaluate() + right_.Evaluate());
		}
	};

	class MinusOperand : public CompositeOperand {
	public:
		MinusOperand(ArithmeticExpression& left, ArithmeticExpression& right) : CompositeOperand(left, right) {};
		virtual std::string Print() override { return ("(" + left_.Print() + "-" + right_.Print() + ")"); }
		virtual double Evaluate() override {
			return (left_.Evaluate() - right_.Evaluate());
		}
	};

	class DivideOperand : public CompositeOperand {
	public:
		DivideOperand(ArithmeticExpression& left, ArithmeticExpression& right) : CompositeOperand(left, right) {};
		virtual std::string Print() override { return ("(" + left_.Print() + "/" + right_.Print() + ")"); }
		virtual double Evaluate() override {
			return (left_.Evaluate() / right_.Evaluate());
		}
	};

	class MultiplyOperand : public CompositeOperand {
	public:
		MultiplyOperand(ArithmeticExpression& left, ArithmeticExpression& right) : CompositeOperand(left, right) {};
		virtual std::string Print() override { return ("(" + left_.Print() + "*" + right_.Print() + ")"); }
		virtual double Evaluate() override {
			return (left_.Evaluate() * right_.Evaluate());
		}
	};

	void Run() {
		NumericOperand a(5.0);
		NumericOperand b(6.0);
		NumericOperand c(10.0);
		NumericOperand d(2.0);

		auto add = PlusOperand(a, b);
		auto subtract = MinusOperand(c, d);
		auto multiply = MultiplyOperand(a, b);
		auto divide = DivideOperand(c, d);

		std::cout << add.Print() << " = " << add.Evaluate() << std::endl;
		std::cout << subtract.Print() << " = " << subtract.Evaluate() << std::endl;
		std::cout << multiply.Print() << " = " << multiply.Evaluate() << std::endl;
		std::cout << divide.Print() << " = " << divide.Evaluate() << std::endl;

		auto first = DivideOperand(divide, multiply);
		auto second = MultiplyOperand(first, subtract);
		auto third = MinusOperand(second, add);

		std::cout << third.Print() << " = " << third.Evaluate() << std::endl;
	}
}