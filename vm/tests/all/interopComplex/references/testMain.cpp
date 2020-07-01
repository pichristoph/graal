//reference testing

#include<stdio.h>
#include<polyglot.h>


int main() {
	PolyglotFile* llFile = Polyglot.evalFile("llvm", "references.so");

	MyClass* c = new llFile.LLVM_MyClass();
	c->i=3;
	int& ref = c->getRef();
	ref = 4;
	if(c->i==4) {
		printf("OK\n");
	} else {
		printf("Error: 0 of 1 passed. c->i should be 4, but is %i\n", c->i);
	}
	delete c;
	free(llFile);
}

