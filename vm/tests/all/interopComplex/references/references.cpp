//reference testing
#include<polyglot.h>

class MyClass {
	public:
		int i;
		int& getRef();
};

POLYGLOT_DECLARE_CLASS(MyClass);

int& MyClass::getRef() {
	int& ref = i;
	return ref;
}

