//CPP
#include<polyglot.h>
#include<iostream>
using namespace std;

class ParentClass {
	protected:
		int val;
	public:
		ParentClass();
};

POLYGLOT_DECLARE_CLASS(ParentClass);

class ChildClass: public ParentClass {
	virtual void setVal(int val);
	virtual int evaluate(int x);
};

POLYGLOT_DECLARE_CLASS(ChildClass);

int main() {
	void* jsFile = polyglot_eval_file("js", "inheritMembers2.js");
	ChildClass* childObj = new ChildClass(cObj);
	void* cObj = polyglot_from_ChildClass(childObj);
	polyglot_invoke(jsFile, "setVal", cObj, 4);
	void* result = polyglot_invoke(jsFile, "evaluate", cObj, polyglot_from_int64(6));
	int64_t intResult = polyglot_as_int64(result);
	cout << "[LLVM] Using JS Member inheritance, result should be 24: " << intResult << endl;
	free(jsFile);
	free(childObj);
}

