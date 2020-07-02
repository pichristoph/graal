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
	void* cObj = polyglot_new_instance(polyglot_ChildClass_typeid());
	ChildClass* childObj = polyglot_as_ChildClass(cObj);
	childObj->setVal(4);
	cout << "[LLVM] Using JS Member inheritance, result should be 24: " << childObj->evaluate(6) << endl;
	free(jsFile);
}

