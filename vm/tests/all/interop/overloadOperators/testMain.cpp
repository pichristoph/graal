//overloadOperators

#include<stdio.h>
#include<polyglot.h>


int main() {
	int nErrors=0;
	PolyglotFile* llFile = Polyglot.evalFile("llvm", "complex.so");

	LLVM_ComplexNumber c1 = llFile->LLVM_ComplexNumber(3,2);
	LLVM_ComplexNumber* c2 = new llFile->LLVM_ComplexNumber(4,5);
	LLVM_ComplexNumber c3 = c1+*c2;
	if(c3.re!=7 || c3.im != 7) {
		nErrors++;
		printf("ERROR! (3,2)+(4,5)=(%f,%f)\n");	
	} 

	delete llFile;
	delete c2;
	
	PolyglotFile* pyFile = Polyglot.evalFile("python", "complex.py");

	Python_ComplexNumber pc1 = pyFile->Python_ComplexNumber(3,2);
	Python_ComplexNumber* pc2 = new pyFile->Python_ComplexNumber(4,5);
	Python_ComplexNumber pc3  = pc1+ *pc2;
	if(pc3.re!=7 || pc3.im != 7) {
		nErrors++;
		printf("ERROR! (3,2)+(4,5)=(%f,%f)\n");	
	} 

	delete pyFile;
	delete pc2;
	if(nErrors==0) {
		printf("OK\n");
	} else {
		printf("%i errors.\n", nErrors);
	}
}
