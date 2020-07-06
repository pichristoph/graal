//CPP
#include<polyglot.h>
#include<iostream>
using namespace std;

class TestClass {
	public:
	int x;
};

POLYGLOT_DECLARE_CLASS(TestClass);

void printX(void* polyglot_obj) {
	TestClass* testClassObj = polyglot_as_TestClass(polyglot_obj);
	cout << "[LLVM] Object created with JS, field value should be 5: " << testClassObj.x << endl; 
}
