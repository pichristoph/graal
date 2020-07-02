//CPP
#include<polyglot.h>
#include<stdlib.h>

class TestClass {
private:
	int x;
public: 
	TestClass(int dX);
	int getX();
};

POLYGLOT_DECLARE_CLASS(TestClass);

TestClass::TestClass(int dX) {
	x=dX;
}

int TestClass::getX() {
	return x;
}
