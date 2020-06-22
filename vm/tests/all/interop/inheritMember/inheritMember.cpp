//inheritMember.cpp
#include<polyglot.h>
#include<stdio.h>
#include<iostream>

PolyglotFile* jsFile = Polyglot::evalFile("js", "inheritMemberClass.js");
PolyglotFile* pyfile = Polyglot::evalFile("python", "inheritMemberClass.py");
PolyglotFile* llvmFile = Polyglot::evalFile("llvm", "inheritMemberClass.so");

//With or without keyword "new"?
JS_LinearFunction* js_m4p2 = new jsFile->LinearFunction(4, 2);
JS_ConstFunction* js_c3 = jsFile->ConstFunction(5);
Python_LinearFunction* py_m4p2 = pyFile->LinearFunction(4, 2);
Python_ConstFunction* py_c3 = pyFile->ConstFunction(5);
LLVM_LinearFunction* ll_m4p2 = llvmFile->LinearFunction(4, 2);
LLVM_ConstFunction* ll_c3 = llvmFile->ConstFunction(5);

cout << "JS: f(3, x->4x+2)=" << js_idP2->evaluate(3) << endl;
cout << "JS: f(2, x->5)=", js_c3.evaluate(2) << endl;
cout << "Py: f(3, x->4x+2)=", py_idP2.evaluate(3) << endl;
cout << "Py: f(2, x->5)=", py_c3.evaluate(2) << endl;
cout << "C++/LLVM: f(3, x->4x+2)=", ll_idP2.evaluate(3) << endl;
cout << "C++/LLVM: f(2, x->5)=", ll_c3.evaluate(2) << endl;

free(js_m4p2);
free(py_m4p2);
free(ll_m4p2);
free(js_c3);
free(py_c3);
free(ll_c3);

free(jsFile);
free(pyFile);
free(llvmFile);




