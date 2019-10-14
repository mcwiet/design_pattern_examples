#include <iostream>
#include <string>
#include <vector>
namespace Factory {
	class Cookie {
	public:
		Cookie(std::vector<std::string> ingredients) : ingredients_(ingredients) {}
		void Eat() {
			std::cout << "You just ate ";
			for (auto it = ingredients_.begin(); it != (ingredients_.end() - 1); ++it) {
				std::cout << *it << ", ";
			}
			std::cout << "and " << ingredients_.back() << "!" << std::endl;
		}
	private:
		std::vector<std::string> ingredients_;
	};

	class Factory {
	public:
		virtual ~Factory() = default;
		virtual Cookie MakeCookie() = 0;
	};

	class GrannysCookieShop : public Factory {
	public:
		virtual Cookie MakeCookie() override { return Cookie({ "eggs", "milk", "sugar", "nail clippings", "lint", "bugs" }); }
	};

	class FranksDiscountCookie : public Factory {
	public:
		virtual Cookie MakeCookie() override { return Cookie({ "eggs", "brown sugar", "butter", "milk", "heart", "soul", "love" }); }
	};

	void Run() {
		while (true) {
			std::cout << "Enter 1 for a cookie from Granny's Cookie Shop" << std::endl;
			std::cout << "Enter 2 for a cookie from Frank's Discount Cookie and Oil Change" << std::endl;
			std::string input;
			std::getline(std::cin, input);
			if (input == "1")
				GrannysCookieShop().MakeCookie().Eat();
			else if (input == "2")
				FranksDiscountCookie().MakeCookie().Eat();
			std::cout << std::endl;
		}
	}
}