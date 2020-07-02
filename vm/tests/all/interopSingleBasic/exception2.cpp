//exceptiontest
#include<polyglot.h>
#include<iostream>
using namespace std;

int main() {
	void* llvmFile = polyglot_eval_file("llvm", "exception1.so");
	try {
		void* val = polyglot_invoke(llvmFile, "run", 3);	//calculate 8/3
		int32_t intVal = polyglot_as_i32(val);
		cout << "[LLVM] Should print JS-calculated value 2: " << intVal << endl;

		val = polyglot_invoke(llvmFile, "run", 0);	//calculate 8/0
		cout << "[LLVM] This should not be printed! Exception thrown by JS has not been caught!" << endl;
	} catch(...) {
		cout << "[LLVM] Intentionally JS-thrown exception has been caught as planned!" << endl;
	} 
	free(llvmFile);
}//main
