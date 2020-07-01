//inheritMethods
#include<polyglot.h>
#include<iostream>
using namespace std;

int main() {

int nErrors = 0;

PolyglotFile* jsFile = Polyglot.evalFile("js", "inheritMethodsClass.js");
PolyglotFile* pyFile = Polyglot.evalFile("python", "inheritMethodsClass.py");
PolyglotFile* llFile = Polyglot.evalFile("llvm", "inheritMethodsClass.so");

JS_ConstAdder* js_add2 = new jsFile->invoke("ConstAdder", 2);
JS_ConstMultiplier* js_mult3 = new jsFile->invoke("ConstMultiplier", 3);
Python_ConstAdder* py_add2 = new pyFile->invoke("ConstAdder", 2);
Python_ConstMultiplier* py_mult3 = new pyFile->invoke("ConstMultiplier", 3);
LLVM_ConstAdder* ll_add2 = new llFile->invoke("ConstAdder", 2);
LLVM_ConstMultiplier* ll_mult3 = new llFile->invoke("ConstMultiplier", 3);
LLVM_ConstAdder* ll_mult3A = ll_mult3;

int jVal = js_add2->getConstObj();
int pVal = py_add2->getConstObj();
int lVal = ll_add2->getConstObj();
if(jVal!=2 || pVal!=2 || lVal != 2) {
	cout << "JS: f(-, ()->2)=" << jVal << endl;
	cout << "Python: f(-, ()->2)=" << pVal << endl;
	cout << "C++/LLVM: f(-, ()->2)=" << lVal << endl;
	nErrors++;
}

jVal = js_mult3->getConstObj();
pVal = py_mult3->getConstObj();
lVal = ll_mult3->getConstObj();
if(jVal!=3 || pVal!=3 || lVal != 3) {
	cout << "JS: f(-, ()->3, inherited)=" << jVal << endl;
	cout << "Python: f(-, ()->3, inherited)=" << pVal << endl;
	cout << "C++/LLVM: f(-, ()->3, inherited)=" << lVal << endl;
	nErrors++;
}

jVal = js_add2->process(5);
pVal = py_add2->process(5);
lVal = ll_add2->process(5);
if(jVal!=7 || pVal!=7 || lVal != 7) {
	cout << "JS: f(5, x->x+2)=" << jVal << endl;
	cout << "Python: f(5, x->x+2)=" << pVal << endl;
	cout << "C++/LLVM: f(5, x->x+2)=" << lVal << endl;
	nErrors++;
}

jVal = js_mult3->process(7);
pVal = py_mult3->process(7);
lVal = ll_mult3->process(7);
if(jVal!=21 || pVal!=21 || lVal != 21) {
	cout << "JS: f(7, x->x*3, overridden)=" << jVal << endl;
	cout << "Python: f(7, x->x*3, overridden)=" << pVal << endl;
	cout << "C++/LLVM: f(7, x->x*3, virtual)=" << lVal << endl;
	nErrors++;
}


//test 'virtuality' of methods

int virtual1 = ll_mult3A->getConstObj();
int virtual2 = ll_mult3A->process(7);
if(virtual1!=3 || virtual2!=21) {
	cout << "f(-, ()->3, inherited)=" << virtual1 << endl;
	cout << "f(7, x->x*3, inherited, virtual)=" << virtual2 << endl;
	nErrors++;
}

if(nErrors==0) {
	cout << "OK" << endl;
} else {
	cout << nErrors << " errors. " << endl;
}

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
