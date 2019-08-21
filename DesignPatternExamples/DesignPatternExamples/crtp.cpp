template <typename DerivedT>
struct CuriousBase {
	void Bar() { asDerived()->foo(); }

private:
	DerivedT const* asDerived() const {
		return static_cast<DerivedT const*>(this);
	}

	DerivedT* asDerived() {
		return static_cast<DerivedT*>(this);
	}
};

struct Derived : CuriousBase<Derived> {
	void foo() {};
};