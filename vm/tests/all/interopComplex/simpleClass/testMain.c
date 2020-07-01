//simpleClass

#include<stdio.h>
#include<polyglot.h>

int main() {

	PolyglotFile* llvmFile = Polyglot.evalFile("llvm","simpleClassPoint.so");
	PolyglotFile* pyFile = Polyglot.evalFile("python", "simpleClassPoint.py");
	PolyglotFile* jsFile = Polyglot.evalFile("js", "simpleClassPoint.js");
	
	/*
	 * maybe, types which are found in other files are imported with a language prefix.
	 * I.e., if in simpleClassPoint.js the type "Point" is found, it is named as JS_Point.
	 */
	
	LLVM_Point lp1 = llvmFile->invoke("Point", 4, 5);
	Python_Point* pp2 = new pyFile->invoke("Point", 1, 9);
	Python_Point pp1 = pyFile->invoke("Point", lp1.getX(), lp1.getY());
	LLVM_Point* lp2 = new llvmFile->invoke("Point", pp2->getX(), pp2->getY());
	JS_Point jp1 = jsFile->invoke("Point", 4, 5);
	JS_Point* jp2 = new jsFile->invoke("Point", 1, 9);
	
	double ld = lp1.distanceTo(lp2);
	double pd = pp2->distanceTo(&pp1);
	double jd = jp1.distanceTo(jp2);
	
	int nErrors = 0;
	if(! lp1.checkMe(4, 5)) {
		nErrors++;
		printf("ERROR! C++/LLVM: p1.y=%i, p1.x=%i\n", lp1.getY(), lp1.getX());
	}
	if(! lp2->checkMe(1, 9)) {
		nErrors++;
		printf("ERROR! C++/LLVM: p2.y=%i, p2.x=%i\n", lp2->getY(), lp2->getX());
	}
	if(! pp1.checkMe(4, 5)) {
		nErrors++;
		printf("ERROR! Python: p1.y=%i, p1.x=%i\n", pp1.getY(), pp1.getX());
		}
	if(! pp2->checkMe(1, 9)) {
		nErrors++;
		printf("ERROR! Python: p2.y=%i, p2.x=%i\n", pp2->getY(), pp2->getX());
	}
	if(! lp1.checkMe(4, 5)) {
		nErrors++;
		printf("ERROR! JS: p1.y=%i, p1.x=%i\n", jp1.getY(), jp1.getX());
	}
	if(! lp2->checkMe(1, 9)) {
		nErrors++;
		printf("ERROR! JS: p2.y=%i, p2.x=%i\n", jp2->getY(), jp2->getX());
	}
	
	if(ld!=5 || jd != 5 || pd != 5) {
		nErrors++;
		printf("LLVM Point distance (should be 5): %f\n", ld);
		printf("JavaScript Point distance (should be 5): %f\n", jd);
		printf("Python Point distance (should be 5): %f\n", pd);
	}
	
	//optional
	double mixed = lp1.distanceTo(pp2);
	if(mixed!=5) {
		printf("Distance between LLVM and Python point, should be 5: %f\n", mixed);
		nErrors++;
	}

	if(nErrors==0) {
		printf("OK\n");
	} else {
		printf("%i errors.\n", nErrors);
	}

	free(lp2);
	free(pp2);
	free(jp2);
	free(llvmFile);
	free(pyFile);
	free(jsFile);
	
}
