//inheritMember
#include<polyglot.h>
#include<stdio.h>
#include<iostream>
using namespace std;

int main() {
	int nErrors=0;
	PolyglotFile* jsFile = Polyglot::evalFile("js", "inheritMember.js");
	PolyglotFile* pyfile = Polyglot::evalFile("python", "inheritMember.py");
	PolyglotFile* llvmFile = Polyglot::evalFile("llvm", "inheritMember.so");
	
	JS_LinearFunction* js_m4p2 = new jsFile->invoke("LinearFunction", 4, 2);
	JS_ConstFunction* js_c3 = new jsFile->invoke("ConstFunction", 5);
	Python_LinearFunction* py_m4p2 = new pyFile->invoke("LinearFunction", 4, 2);
	Python_ConstFunction* py_c3 = new pyFile->invoke("ConstFunction", 5);
	LLVM_LinearFunction* ll_m4p2 = new llvmFile->invoke("LinearFunction", 4, 2);
	LLVM_ConstFunction* ll_c3 = new llvmFile->invoke("ConstFunction", 5);
	
	int val = js_m4p2->evaluate(3);
	if(val != 14) {
		nErrors++;
		cout << "ERROR! JS: f(3, x->4x+2)=" << val << endl;
	}
	
	val = js_c3.evaluate(2);
	if(val != 5) {
		nErrors++;
		cout << "ERROR! JS: f(2, x->5)=" << val << endl;
	}

	val = py_m4p2->evaluate(3);
	if(val != 14) {
		nErrors++;
		cout << "ERROR! Python: f(3, x->4x+2)=" << val << endl;
	}
	
	val = py_c3.evaluate(2);
	if(val != 5) {
		nErrors++;
		cout << "ERROR! Python: f(2, x->5)=" << val << endl;
	}

	val = ll_m4p2->evaluate(3);
	if(val != 14) {
		nErrors++;
		cout << "ERROR! C++/LLVM: f(3, x->4x+2)=" << val << endl;
	}
	
	val = ll_c3.evaluate(2);
	if(val != 5) {
		nErrors++;
		cout << "ERROR! C++/LLVM: f(2, x->5)=" << val << endl;
	}


	if(nErrors==0) {
		cout << "OK" << endl;
	} else {
		cout << nErrors << " errors." << endl;
	}
	
	free(js_m4p2);
	free(py_m4p2);
	free(ll_m4p2);
	free(js_c3);
	free(py_c3);
	free(ll_c3);
	
	free(jsFile);
	free(pyFile);
	free(llvmFile);
}




