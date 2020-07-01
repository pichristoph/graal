//CPP
#include<polyglot.h>
#include<iostream>
using namespace std;

class MyClass {
	public:
	virtual int foo();
};

POLYGLOT_DECLARE_CLASS(MyClass);

void printFooResult(void* polyglot_ptr) {
	void* jsFile = polyglot_eval_file("js", "simpleMethodCall1.js");
	MyClass* myClass = polyglot_as_MyClass(polyglot_ptr);
	cout << "[LLVM] " << myClass->foo() << endl;
	free(myClass);
	free(jsFile);
}

