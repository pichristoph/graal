//overloadOperators.cpp

#include<stdio.h>
#include<polyglot.h>


int main() {
	
	PolyglotFile* llFile = Polyglot.evalFile("llvm", "complex.so");

	llFile->LLVM_Complex c1(3,2);
	llFile->LLVM_Complex c2(4,5);
	llFile->LLVM_Complex c3 = c1+c2;
	printf("(3,2)+(4,5)=(%f,%f)\n", c3.re, c3.im);
}
