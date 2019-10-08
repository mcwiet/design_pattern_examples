#include <iostream>
#include <string>

namespace FactoryAbstract {
	class Product {
	public:
		virtual ~Product() = default;
		const std::string& GetName() { return name_; }
	protected:
		Product(std::string name) : name_(name) {}
		std::string name_ = "";
	};

	class Phone : public Product {
	public:
		virtual ~Phone() = default;
	protected:
		Phone(std::string name) : Product(name + "Phone") {}
	};

	class PhoneCharger : public Product {
	public:
		virtual ~PhoneCharger() = default;
	protected:
		PhoneCharger(std::string name) : Product(name + "Charger") {}
	};

	class PhoneCase : public Product {
	public:
		virtual ~PhoneCase() = default;
	protected:
		PhoneCase(std::string name) : Product(name + "Case") {}
	};

	class IPhone : public Phone { public: IPhone() : Phone("IPhone ") {} };
	class IPhoneCharger : public PhoneCharger { public: IPhoneCharger() : PhoneCharger("IPhone ") {} };
	class IPhoneCase : public PhoneCase { public: IPhoneCase() : PhoneCase("IPhone ") {} };

	class AndroidPhone : public Phone { public: AndroidPhone() : Phone("Android ") {} };
	class AndroidCharger : public PhoneCharger { public: AndroidCharger() : PhoneCharger("Android ") {} };
	class AndroidCase : public PhoneCase { public: AndroidCase() : PhoneCase("Android ") {} };

	class ProductFactory {
	public:
		virtual ~ProductFactory() = default;
		virtual Phone* BuildPhone() = 0;
		virtual PhoneCharger* BuildCharger() = 0;
		virtual PhoneCase* BuildCase() = 0;
	};

	class IPhoneFactory : public ProductFactory {
	public:
		virtual IPhone* BuildPhone() override { return new IPhone; }
		virtual IPhoneCharger* BuildCharger() override { return new IPhoneCharger; }
		virtual IPhoneCase* BuildCase() override { return new IPhoneCase; }
	};

	class AndroidFactory : public ProductFactory {
	public:
		virtual AndroidPhone* BuildPhone() override { return new AndroidPhone; }
		virtual AndroidCharger* BuildCharger() override { return new AndroidCharger; }
		virtual AndroidCase* BuildCase() override { return new AndroidCase; }
	};

	class ProductLineFactory {
	public:
		IPhoneFactory* CreateIPhoneFactory() { return new IPhoneFactory; }
		AndroidFactory* CreateAndroidFactory() { return new AndroidFactory; }
	};

	void Run() {
		while (true) {
			std::cout << "Do you use Apple products or Android products?" << std::endl;
			std::string input;
			std::getline(std::cin, input);
			ProductFactory* factory = nullptr;
			if (input == "Apple")
				factory = ProductLineFactory().CreateIPhoneFactory();
			else if (input == "Android")
				factory = ProductLineFactory().CreateAndroidFactory();
			else
				continue;

			std::cout << "Do you need a phone, a charger, or a case?" << std::endl;
			std::getline(std::cin, input);
			Product* product = nullptr;
			if (input == "phone")
				product = factory->BuildPhone();
			else if (input == "charger")
				product = factory->BuildCharger();
			else if (input == "case")
				product = factory->BuildCase();
			else
				continue;

			std::cout << "You just purchased an " << product->GetName() << "." << std::endl << std::endl;
		}
	}
}