//exceptiontest
#include<polyglot.h>
#include<iostream>
using namespace std;

int main() {

PolyglotFile* pyFile = polyglot.evalFile("py", "throwingProgram.py")

int pass=0;

try {
	pyFile->invoke("run", 5);	//calculate 5/0
	cout << "This should not be printed. (Planned) exception has not been thrown." << endl; 
} catch(...) {
	pass++; //intentionally thrown exception has been caught
}

free(pyFile);

PolyglotFile* llFile = polyglot.evalFile("llvm", "throwingProgram.so")

try {
	llFile->invoke("run", 5);	//calculate 5/0
	cout << "This should not be printed. (Planned) exception has not been thrown." << endl;
} catch(...) {
	pass++; //intentionally thrown exception has been caught
}
free(llFile);

if(pass==2) {
	cout << "OK" << endl;
} else {
	cout << "ERROR. Passed: " << pass << " of 2." << endl;
}

}//main
