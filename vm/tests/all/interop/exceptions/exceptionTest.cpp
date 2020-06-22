//exceptiontest.cpp
#include<polyglot.h>
#include<iostream>

int main() {

PolyglotFile* pyFile = polyglot.evalFile("py", "throwingProgram.py")

try {
	cout << "calculate 5/0: " << endl;
	pyFile->invoke("run", 5);
	cout << "This should not be printed." << endl;
} catch(...) {
	cout << "(Intentionally thrown) Exception has been caught" << endl;
}

free(pyFile);

PolyglotFile* llFile = polyglot.evalFile("llvm", "throwingProgram.so")

try {
	cout << "calculate 5/0: " << endl;
	llFile->invoke("run", 5);
	cout << "This should not be printed." << endl;
} catch(...) {
	cout << "(Intentionally thrown) Exception has been caught" << endl;
}
free(llFile);

}
