//overloadOperators.cpp

#include<polyglot.h>

class Complex {
	public: 
		double re;
		double im;
		Complex(double reV, double imV);
};

POLYGLOT_DECLARE_CLASS(Complex);

Complex::Complex(double reV, double imV) {
	re=reV;
	im=imV;
}

Complex operator+(const Complex& c1, const Complex& c2) {
	Complex c(c1.re+c2.re, c1.im+c2.im);
	return c;
}


