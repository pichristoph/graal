//simpleClass.cpp

#include<stdio.h>
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
	
	LLVM_Point* lp1 = llvmFile->init_Point(4, 5);
	Python_Point* pp2 = pyFile->init_Point(1, 9);
	Python_Point* pp1 = pyFile->init_Point(getX(lp1), getY(lp1));
	LLVM_Point* lp2 = llvmFile->init_Point(getX(pp2), getY(pp2));
	JS_Point* jp1 = jsFile->init_Point(4, 5);
	JS_Point* jp2 = jsFile->init_Point(1, 9);
	
	double ld = distanceTo(lp1, lp2);
	double pd = distanceTo(pp2, pp1);
	double jd = distanceTo(jp1, jp2);
	
	printf("LLVM Points: \n");
	printMe(lp1); //OR printMe_Point(lp1); if "class"/struct information needed (i.e. foo_typeName(args))
	printMe(lp2);
	printf("Python Points: \n");
	printMe(pp1);
	printMe(pp2);
	printf("Javascript Points: \n");
	printMe(jp1);
	printMe(jp2);
	
	printf("LLVM Point distance (should be 5): %f\n",ld);
	printf("JavaScript Point distance (should be 5): %f\n", jd);
	printf("Python Point distance (should be 5): %f\n", pd);
	
	//optional and not possible that easily in C++ (type cast/...?)	
	double mixed = distanceTo(lp1, pp2)
	printf("Distance between LLVM and Python point, should be 5: %f\n", mixed);

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
