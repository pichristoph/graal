//reference testing

#include<stdio.h>
#include<polyglot.h>


int main() {
	PolyglotFile* llFile = Polyglot.evalFile("llvm", "referencesClass.so");

	MyClass* c = new llFile.LLVM_MyClass();
	c->i=3;
	int& ref = c->getRef();
	ref = 4;
	printf("reference to c.i has been set to 4. c.i=%i\n",c->i);
	delete c;
	free(llFile);
}

