//CPP
#include<polyglot.h>
#include<iostream>
using namespace std;

int main() {
	void* jsFile = Polyglot.evalFile("js", "arrays2.js");

	void* ret = polyglot_invoke(jsFile, "getSquaredArray", 5);
	int64_t* arr = polyglot_as_i64_array(ret);
	cout << "[JS] LLVM-Array with length 5 (actual: " << "?" << "), and arr[4] = 16 (actual: " << *(arr+4) << ")" << endl;
	free(arr); 
	free(jsFile);
}
