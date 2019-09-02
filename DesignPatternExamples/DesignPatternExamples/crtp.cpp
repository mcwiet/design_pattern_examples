#include <iostream>

namespace CRTP {

	template <typename DerivedT>
	struct CuriousBase {
		void Foo() {
			std::cout << "calling Foo() as base..." << std::endl;
			asDerived()->Bar();
		}

	private:
		DerivedT const* asDerived() const {
			return static_cast<DerivedT const*>(this);
		}

		DerivedT* asDerived() {
			return static_cast<DerivedT*>(this);
		}
	};

	struct Derived : CuriousBase<Derived> {
		void Bar() {
			std::cout << "calling Bar() as derived..." << std::endl;
		}
	};

	struct DerivedIncomplete : CuriousBase<DerivedIncomplete> {
		void NotBar() {
			std::cout << "should never be called..." << std::endl;
		}
	};

	void Run() {
		CuriousBase<Derived> good_func = Derived();
		good_func.Foo();
		CuriousBase<DerivedIncomplete> bad_func = DerivedIncomplete();
		//bad_func.Foo(); // doesn't compile
	}
}