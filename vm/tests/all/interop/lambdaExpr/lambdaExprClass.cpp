//lambdaExprClass.cpp
#include<polyglot.h>

int identity(int x) {
	return x;
}

MyClass{
	public:
	int (*foo)(int);
	MyClass();
};

POLYGLOT_DECLARE_CLASS(MyClass);

MyClass::MyClass() {
	foo = identity;
}

