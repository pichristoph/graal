//CPP
#include<polyglot.h>
#include<iostream>
using namespace std;

class A {
	public:
		virtual void foo1();
		virtual void foo2();
};

POLYGLOT_DECLARE_CLASS(A);

A::foo1() {
	cout << "A::foo1()" << endl;
}
A::foo2() {
	cout << "A::foo2()" << endl;
}

class B:public A {
	public:
		void foo2();
};

POLYGLOT_DECLARE_CLASS(B);

B::foo2() {
	cout << "B::foo2()" << endl;
}
