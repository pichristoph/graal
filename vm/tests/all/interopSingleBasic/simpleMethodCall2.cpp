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
	void* jsFile = polyglot_eval_file("js", "simpleMethodCall1.js");
	MyClass* myClassObj = new MyClass();
	void* fooResult = polyglot_invoke(jsFile, "printFooResult", myClassObj);
	int fooValue = polyglot_as_int(fooResult);
	cout << "[LLVM] Now, it should print \"748\": " << fooResult << endl;
	free(myClassObj);
	free(jsFile);
}
