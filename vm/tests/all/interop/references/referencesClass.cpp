//reference testing

class MyClass {
	public:
		int i;
		int& getRef();
};

int& MyClass::getRef() {
	int& ref = i;
	return ref;
}

