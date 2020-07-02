//CPP
#include<polyglot.h>
#include<iostream>
using namespace std;

class MyClass {
	public:
	int foo() {
		return 748;
	}
};

int main() {
	void* jsFile = polyglot_eval_file("js", "simpleMethodCall2.js");
	MyClass* myClassObj = new MyClass();
	void* fooResult = polyglot_invoke(jsFile, "printFooResult", myClassObj);
	int32_t fooValue = polyglot_as_i32(fooResult);
	cout << "[LLVM] Now, it should print \"748\": " << fooResult << endl;
	free(myClassObj);
	free(jsFile);
}
