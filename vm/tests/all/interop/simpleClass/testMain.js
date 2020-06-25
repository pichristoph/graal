//simpleClass

nErrors = 0;
var llvmFile = polyglot.evalFile("llvm","simpleClassPoint.so");
var pyFile = polyglot.evalFile("python", "simpleClassPoint.py");
var jsFile = polyglot.evalFile("js", "simpleClassPoint.js");

lp1 = new llvmFile.Point(4, 5);
pp2 = new pyFile.Point(1, 9);
pp1 = new pyFile.Point(lp1.getX(), lp1.getY());
lp2 = new llvmFile.Point(pp2.getX(), pp2.getY());

jp1 = new jsFile.Point(4, 5);
jp2 = new jsFile.Point(1, 9);

ld = lp1.distanceTo(lp2);
pd = pp2.distanceTo(pp1);
jd = jp1.distanceTo(jp2);

if(! lp1.checkMe(4, 5)) {
	nErrors++;
	console.log("ERROR! C++/LLVM: p1.y=",lp1.getY(),", p1.x=",lp1.getX());
}
if(! lp2.checkMe(1, 9)) {
	nErrors++;
	console.log("ERROR! C++/LLVM: p2.y=",lp2.getY(),", p2.x=",lp2.getX());
}
if(! pp1.checkMe(4, 5)) {
	nErrors++;
	console.log("ERROR! Python: p1.y=",pp1.getY(),", p1.x=",pp1.getX());
}
if(! pp2.checkMe(1, 9)) {
	nErrors++;
	console.log("ERROR! Python: p2.y=",pp2.getY(),", p2.x=",pp2.getX());
}
if(! lp1.checkMe(4, 5)) {
	nErrors++;
	console.log("ERROR! JS: p1.y=",jp1.getY(),", p1.x=",jp1.getX());
}
if(! lp2.checkMe(1, 9)) {
	nErrors++;
	console.log("ERROR! JS: p2.y=",jp2.getY(),", p2.x=",jp2.getX());
}

if(ld!=5 || jd != 5 || pd != 5) {
	nErrors++;
	console.log("LLVM Point distance (should be 5): ", ld);
	console.log("JavaScript Point distance (should be 5): ", jd);
	console.log("Python Point distance (should be 5): ", pd);
}

//optional
mixed = lp1.distanceTo(pp2);
if(mixed!=5) {
	console.log("Distance between LLVM and Python point, should be 5: ", mixed);
	nErrors++;
}

if(nErrors==0) {
	console.log("OK");
} else {
	console.log(nErrors, " errors.");
}
