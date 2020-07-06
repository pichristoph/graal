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

class B:public A {
	public:
		virtual void foo2();
};

POLYGLOT_DECLARE_CLASS(B);

int main() {
	llvmFile = Polyglot.evalFile("js", "inheritMethods2.js");

	//A has methods foo1(), foo2()
	void* ap = llvmFile.createA(); 
	//B extends A, has method foo2() only
	void* bp = llvmFile.createB();
	void* bbp = llvmFile.createB();

	A* a = polyglot_as_A(ap);
	B* b = polyglot_as_B(bp);
	A* bb = polyglot_as_A(bbp);

	cout << "A a.foo1() should lead to A::foo1: ";
	a->foo1();
	cout << "B b.foo1() should lead to: A::foo1: ";
	b->foo1();
	cout << "A b.foo1() should lead to: A::foo1: ";
	bb->foo2();
	cout << endl;
	cout << "A a.foo2() should lead to: A::foo2: ";
	a->foo2();
	cout << "B b.foo2() should lead to: B::foo2: ";
	b->foo2();
	cout << "A b.foo2() should lead to: B::foo2: ";
	bb->foo2();
	cout << endl;

	free(llvmFile);
}
