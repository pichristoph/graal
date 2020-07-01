//simpleClass

#include<iostream>
#include<polyglot.h>
using namespace std;

int main() {

	PolyglotFile* llvmFile = Polyglot::evalFile("llvm","simpleClassPoint.so");
	PolyglotFile* pyFile = Polyglot::evalFile("python", "simpleClassPoint.py");
	PolyglotFile* jsFile = Polyglot::evalFile("js", "simpleClassPoint.js");
	
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
		cout << "ERROR! C++/LLVM: p1.y=" << lp1.getY() << ", p1.x=" << lp1.getX() << endl;
	}
	if(! lp2->checkMe(1, 9)) {
		nErrors++;
		cout << "ERROR! C++/LLVM: p2.y=" << lp2->getY() << ", p2.x=" << lp2->getX() << endl;
	}
	if(! pp1.checkMe(4, 5)) {
		nErrors++;
		cout << "ERROR! Python: p1.y=" << pp1.getY() << ", p1.x=" << pp1.getX() << endl;
		}
	if(! pp2->checkMe(1, 9)) {
		nErrors++;
		cout << "ERROR! Python: p2.y=" << pp2->getY() << ", p2.x=" << pp2->getX() << endl;
	}
	if(! lp1.checkMe(4, 5)) {
		nErrors++;
		cout << "ERROR! JS: p1.y=" << jp1.getY() << ", p1.x=" << jp1.getX() << endl;
	}
	if(! lp2->checkMe(1, 9)) {
		nErrors++;
		cout << "ERROR! JS: p2.y=" << jp2->getY() << ", p2.x=" << jp2->getX() << endl;
	}
	
	if(ld!=5 || jd != 5 || pd != 5) {
		nErrors++;
		cout << "LLVM Point distance (should be 5): " <<  ld << endl;
		cout << "JavaScript Point distance (should be 5): " << jd << endl;
		cout << "Python Point distance (should be 5): " << pd << endl;
	}
	
	//optional
	double mixed = lp1.distanceTo(pp2);
	if(mixed!=5) {
		cout << "Distance between LLVM and Python point, should be 5: " << mixed << endl;
		nErrors++;
	}

	if(nErrors==0) {
		cout << "OK" << endl;
	} else {
		cout << nErrors << " errors."<< endl;
	}

	free(lp2);
	free(pp2);
	free(jp2);
	free(llvmFile);
	free(pyFile);
	free(jsFile);
	
}
