//simpleClass.cpp

#include<iostream.h>
#include<polyglot.h>

int main() {

	PolyglotFile* llvmFile = Polyglot::evalFile("llvm","simpleClassPoint.so");
	PolyglotFile* pyFile = Polyglot::evalFile("python", "simpleClassPoint.py");
	PolyglotFile* jsFile = Polyglot::evalFile("js", "simpleClassPoint.js");
	
	/*
	 * maybe, types which are found in other files are imported with a language prefix.
	 * I.e., if in simpleClassPoint.js the type "Point" is found, it is named as JS_Point. 
	 * If not possible, maybe every polyglot call returns a Value*, and we might call valueObj->invoke("methodName", args). 
	 */
	
	LLVM_Point* lp1 = llvmFile->Point(4, 5);
	Python_Point* pp2 = pyFile->Point(1, 9);
	Python_Point* pp1 = pyFile->Point(lp1->getX(), lp1->getY());
	LLVM_Point* lp2 = llvmFile->Point(pp2->getX(), pp2->getY());
	JS_Point* jp1 = jsFile->Point(4, 5);
	JS_Point* jp2 = jsFile->Point(1, 9);
	
	double ld = lp1->distanceTo(lp2);
	double pd = pp2->distanceTo(pp1);
	double jd = jp1->distanceTo(jp2);
	
	
	cout << "LLVM Points: ";
	lp1->printMe();
	lp2->printMe();
	cout << "Python Points: ";
	pp1->printMe();
	pp2->printMe();
	cout << "Javascript Points: ";
	jp1->printMe();
	jp2->printMe();
	
	cout << "LLVM Point distance (should be 5): " << ld << endl;
	cout << "JavaScript Point distance (should be 5): " << jd << endl;
	cout << "Python Point distance (should be 5): " << pd << endl;
	
	//optional and not possible that easily in C++ (type cast/...?)	
	double mixed = lp1->distanceTo(pp2)
	cout << "Distance between LLVM and Python point, should be 5: " << mixed << endl;

	free(lp1);
	free(lp2);
	free(pp1);
	free(pp2);
	free(jp1);
	free(jp2);
	free(llvmFile);
	free(pyFile);
	free(jsFile);
	
}
