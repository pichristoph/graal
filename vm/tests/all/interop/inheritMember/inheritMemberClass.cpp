//inheritMemberClass.cpp
#include<polyglot.h>
#include<stdio.h>


class LinearFunction {
	protected:
		int k;
		int d;
	public:
		LinearFunction(int k, int d);
		virtual int evaluate(int x);
};

POLYGLOT_DECLARE_CLASS(LinearFunction);

class ConstFunction: public LinearFunction {
	public:
		ConstFunction(int d);
};

POLYGLOT_DECLARE_CLASS(ConstFunction);

LinearFunction::LinearFunction(int kVal, int dVal) {
	k=kVal;
	d=dVal;
}

int LinearFunction::evaluate(x) {
	return k*x+d;
}

ConstFunction::ConstFunction(int dVal) : base(0, dVal) {}
	

