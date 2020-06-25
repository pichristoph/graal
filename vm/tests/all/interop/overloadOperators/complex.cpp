//overloadOperators.cpp

#include<polyglot.h>

class ComplexNumber {
	public: 
		double re;
		double im;
		ComplexNumber(double reV, double imV);
};

POLYGLOT_DECLARE_CLASS(ComplexNumber);

ComplexNumber::ComplexNumber(double reV, double imV) {
	re=reV;
	im=imV;
}

ComplexNumber operator+(const ComplexNumber& c1, const ComplexNumber& c2) {
	ComplexNumber c(c1.re+c2.re, c1.im+c2.im);
	return c;
}


