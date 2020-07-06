//CPP
#include<polyglot.h>

class ParentClass {
	protected:
		int val;
	public:
		ParentClass();
};

POLYGLOT_DECLARE_CLASS(ParentClass);

ParentClass::ParentClass() {
	val=0;
}

class ChildClass: public ParentClass {
	public:
	ChildClass();
	void setVal(int value);
	int evaluate(int x);
};

POLYGLOT_DECLARE_CLASS(ChildClass);

ChildClass::ChildClass():ParentClass() {	}

void ChildClass::setVal(int value) {
	val = value;
}

int ChildClass::evaluate(int x) {
	return val*x;
}

void processAndEvaluate(void* cObj, void* evalVal) {
	ChildClass* childObj = polyglot_as_ChildClass(cObj);
	int64_t val = polyglot_as_int64(evalVal);
	cout << "[LLVM] Using JS Object and Member inheritance, result should be 24: " << childObj->evaluate(val) << endl;
	free(jsFile);
}
