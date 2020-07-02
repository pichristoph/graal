//CPP
#include<polyglot.h>
#include<iostream>
using namespace std;

class TestClass {
	public:
	virtual TestClass(int x);
	virtual int getX();
};

POLYGLOT_DECLARE_CLASS(TestClass);

int main() {
	void* jsFile = polyglot_eval_file("js", "constructor2.js");
	void* ret = polyglot_new_instance(polyglot_TestClass_typeid());
	TestClass* testClassObj = polyglot_as_TestClass(ret);
	cout << "[LLVM] Object created with JS, field value should be 5: " << testClassObj.getX() << endl; 
}
