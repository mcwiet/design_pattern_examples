#include <iostream>
#include <memory>

class AbstractMadLib {
public:
	AbstractMadLib() = default;
	virtual ~AbstractMadLib() = default;

	void OutputMadLib() {
		std::cout << "The Raleigh Software Group is full of ";
		OutputAdjective();
		std::cout << " people! They all deserve ";
		OutputPluralNoun();
		std::cout << "!" << std::endl;
	}

protected:
	virtual void OutputAdjective() = 0;
	virtual void OutputPluralNoun() = 0;
};

class MadLib1 : public AbstractMadLib {
public:
	MadLib1() = default;
	virtual ~MadLib1() = default;

private:
	virtual void OutputAdjective() override {
		std::cout << "smart";
	}

	virtual void OutputPluralNoun() override {
		std::cout << "enormous raises";
	}
};

class MadLib2 : public AbstractMadLib {
public:
	MadLib2() = default;
	virtual ~MadLib2() = default;

private:
	virtual void OutputAdjective() override {
		std::cout << ".....";
	}

	virtual void OutputPluralNoun() override {
		std::cout << "......";
	}
};

int main() {
	std::unique_ptr<AbstractMadLib> ml1 = std::make_unique<MadLib1>();
	std::unique_ptr<AbstractMadLib> ml2 = std::make_unique<MadLib2>();

	std::cout << "Outputting MadLib1: " << std::endl;
	ml1->OutputMadLib();
	std::cout << std::endl;
	std::cout << "Outputting MadLib2: " << std::endl;
	ml2->OutputMadLib();
}