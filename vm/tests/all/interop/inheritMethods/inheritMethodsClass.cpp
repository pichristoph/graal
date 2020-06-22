//inheritMethodsClass.cpp
#include<polyglot.h>

class ConstAdder {
	protected:
		int constObj;
	public:
	ConstAdder(int x);
	virtual int process(int y);
	virtual int getConstObj();
};

DECLARE_POLYGLOT_CLASS(ConstAdder);

class ConstMultiplier extends ConstAdder {
	public:
		ConstMultiplier(int x);
		int process(int y);
};

DECLARE_POLYGLOT_CLASS(ConstMultiplier);

ConstAdder::ConstAdder(int x) {
	constObj = x;
}

int ConstAdder::process(int y) {
	return y+constObj;
}

int ConstAdder::getConstObj() {
	return constObj;
}

ConstMultiplier::ConstMultiplier(int x):ConstAdder(x) {}

int ConstMultiplier::process(int y) {
	return y*constObj;
}
