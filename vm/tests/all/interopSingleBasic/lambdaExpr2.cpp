//CPP
#include<polyglot.h>
#include<iostream>
using namespace std;

class AClass {
	public:
	int (*foo)(int);
}

POLYGLOT_DECLARE_CLASS(AClass);

int doubleAndIncrement(int x) {
	return 2*x+1;
}

int main() {
	void* jsFile = polyglot_eval_file("js", "lambdaExpr2.js");
	
	void* aPoly = polyglot_invoke(jsFile, "createAClass");
	AClass* aObj = polyglot_as_AClass(aPoly);
	int val = aObj->foo(4);
	cout << "[LLVM] calling JS identity (x -> x) of 4 leads to: " << val << endl;
	aObj->foo = &doubleAndIncrement;
	val = aObj->foo(4);
	cout << "[LLVM] calling (x -> 2x-1) of 4 leads to: " << val << endl;

	free(jsFile);
}


