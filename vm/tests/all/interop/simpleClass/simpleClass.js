//simpleClass.js

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

console.log("LLVM Points: ");
lp1.printMe();lp2.printMe();
console.log("Python Points: ");
pp1.printMe();pp2.printMe();
console.log("JavaScript Points: ");
jp1.printMe();jp2.printMe();

console.log("LLVM Point distance (should be 5): ");
console.log(ld);
console.log("Python Point distance (should be 5): ");
console.log(pd);
console.log("JavaScript Point distance (should be 5): ");
console.log(jd);

//optional
mixed = lp1.distanceTo(pp2);
console.log("Distance between LLVM and Python point, should be 5: ");
console.log(mixed);




