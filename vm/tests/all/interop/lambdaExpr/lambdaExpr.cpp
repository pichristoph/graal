//lambdaExpr.cpp
#include<polyglot.h>
#include<iostream>

int doubleAndIncrement(int x) {
	return x*2+1;
}

int main() {

PolyglotFile* llFile = Polyglot.evalFile("llvm", "lambdaExprClass.so");
PolyglotFile* jsFile = Polyglot.evalFile("js", "lambdaExprClass.js");
PolyglotFile* pyFile = Polyglot.evalFile("python", "lambdaExprClass.py");

LLVM_MyClass* c = new llFile->MyClass();
//OR
LLVM_MyClass* c = llFile->invoke("MyClass");
cout << "calling f(8, x->x) leads to " << c->foo(8) << endl;
c->foo = doubleAndIncrement;
cout << "calling f(8, x->2*x+1) leads to " << c->foo(8) << endl;

JS_MyClass* cJ = jsFile->invoke("MyClass");
cout << "calling f(8, x->x) leads to " << c->foo(8) << endl;
cJ->foo = doubleAndIncrement;
cout << "calling f(8, x->2*x+1) leads to " << c->foo(8) << endl;

Python_MyClass* cP = pyFile->invoke("MyClass");
cout << "calling f(8, x->x) leads to " << c->foo(8) << endl;
cP->foo = doubleAndIncrement;
cout << "calling f(8, x->2*x+1) leads to " << c->foo(8) << endl;

delete cP;
delete cJ;
delete c;

delete llFile;
delete jsFile;
delete pyFile;
}
