//overloadOperators.cpp

#include<stdio.h>
#include<polyglot.h>


int main() {
	
	PolyglotFile* llFile = Polyglot.evalFile("llvm", "complex.so");

	LLVM_ComplexNumber c1 = llFile->LLVM_ComplexNumber(3,2);
	LLVM_ComplexNumber c2 = llFile->LLVM_ComplexNumber(4,5);
	LLVM_ComplexNumber c3 = llFile->LLVM_ComplexNumber c3 = c1+c2;
	printf("(3,2)+(4,5)=(%f,%f)\n", c3.re, c3.im);

	delete llFile;
	
	PolyglotFile* pyFile = Polyglot.evalFile("python", "complex.py");

	Python_ComplexNumber c1 = pyFile->Python_ComplexNumber(3,2);
	Python_ComplexNumber c2 = pyFile->Python_ComplexNumber(4,5);
	Python_ComplexNumber c3 = pyFile->Python_ComplexNumber c3 = c1+c2;
	printf("(3,2)+(4,5)=(%f,%f)\n", c3.re, c3.im);

	delete pyFile;
}
