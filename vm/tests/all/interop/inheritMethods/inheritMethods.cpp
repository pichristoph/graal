//inheritMethods.cpp
#include<polyglot.h>
#include<iostream>

int main() {

PolyglotFile* jsFile = Polyglot.evalFile("js", "inheritMethodsClass.js");
PolyglotFile* pyFile = Polyglot.evalFile("python", "inheritMethodsClass.py");
PolyglotFile* llFile = Polyglot.evalFile("llvm", "inheritMethodsClass.so");

JS_ConstAdder* js_add2 = jsFile->invoke("ConstAdder", 2);
JS_ConstMultiplier* js_mult3 = jsFile->invoke("ConstMultiplier", 3);

cout << "f(-, ()->2)=" << js_add2->getConstObj() << endl;
cout << "f(-, ()->3, inherited)=" << js_mult3->getConstObj() << endl;
cout << "f(5, x->x+2)=" << js_add2->process(5) << endl;
cout << "f(7, x->x*3)=" << js_mult3->process(7) << endl;

Python_ConstAdder* py_add2 = pyFile->invoke("ConstAdder", 2);
Python_ConstMultiplier* py_mult3 = pyFile->invoke("ConstMultiplier", 3);

cout << "f(-, ()->2)=" << py_add2->getConstObj() << endl;
cout << "f(-, ()->3, inherited)=" << py_mult3->getConstObj() << endl;
cout << "f(5, x->x+2)=" << py_add2->process(5) << endl;
cout << "f(7, x->x*3)=" << py_mult3->process(7) << endl;

LLVM_ConstAdder* ll_add2 = llFile->invoke("ConstAdder", 2);
LLVM_ConstMultiplier* ll_mult3 = llFile->invoke("ConstMultiplier", 3);

cout << "f(-, ()->2)=" << ll_add2->getConstObj() << endl;
cout << "f(-, ()->3, inherited)=" << ll_mult3->getConstObj() << endl;
cout << "f(5, x->x+2)=" << ll_add2->process(5) << endl;
cout << "f(7, x->x*3)=" << ll_mult3->process(7) << endl;

free(js_add2);
free(py_add2);
free(ll_add2);
free(js_mult3);
free(py_mult3);
free(ll_mult3);
free(jsFile);
free(pyFile);
free(llFile);
}
