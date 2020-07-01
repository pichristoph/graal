//lambdaExpr.cpp
#include<polyglot.h>
#include<iostream>
using namespace std;

int doubleAndIncrement(int x) {
	return x*2+1;
}

int main() {

PolyglotFile* llFile = Polyglot.evalFile("llvm", "lambdaExprClass.so");
PolyglotFile* jsFile = Polyglot.evalFile("js", "lambdaExprClass.js");
PolyglotFile* pyFile = Polyglot.evalFile("python", "lambdaExprClass.py");

int nErrors=0;

LLVM_MyClass* c = new llFile->invoke("MyClass");
int val = c->foo(8);
if(val!=8) {
	nErrors++;
	cout << "C++/LLVM: calling f(8, x->x) leads to " << val << endl;
}
c->foo = doubleAndIncrement;
val = c->foo(8);
if(val!=17) {
	nErrors++;
	cout << "C++/LLVM: calling f(8, x->x) leads to " << val << endl;
}

JS_MyClass* cJ = new jsFile->invoke("MyClass");
val = cJ->foo(8);
if(val!=8) {
	nErrors++;
	cout << "JS: calling f(8, x->x) leads to " << val << endl;
}
c->foo = doubleAndIncrement;
val = cJ->foo(8);
if(val!=17) {
	nErrors++;
	cout << "JS: calling f(8, x->x) leads to " << val << endl;
}

Python_MyClass* cP = new pyFile->invoke("MyClass");
val = cP->foo(8);
if(val!=8) {
	nErrors++;
	cout << "Python: calling f(8, x->x) leads to " << val << endl;
}
c->foo = doubleAndIncrement;
val = cP->foo(8);
if(val!=17) {
	nErrors++;
	cout << "Python: calling f(8, x->x) leads to " << val << endl;
}

if(nErrors==0) {
	cout << "OK" << endl;
} else {
	cout << nErrors << " errors." << endl;
}

delete cP;
delete cJ;
delete c;

delete llFile;
delete jsFile;
delete pyFile;
}
