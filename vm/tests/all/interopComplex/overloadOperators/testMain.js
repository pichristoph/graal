//overloadOperators

nErrors = 0;
var llFile = Polyglot.evalFile("llvm", "complex.so");
c1 = new llFile.ComplexNumber(3,2);
c2 = new llFile.ComplexNumber(4,5);
c3 = c1+c2;
if(c3.re!=7 || c3.im != 7) {
	nErrors++;
	console.log("ERROR! (3,2)+(4,5)=(", c3.re, ",", c3.im, ")");	
} 

var pyFile = Polyglot.evalFile("python", "complex.py");
c1 = new llFile.ComplexNumber(3,2);
c2 = new llFile.ComplexNumber(4,5);
c3 = c1+c2;
if(c3.re!=7 || c3.im != 7) {
	nErrors++;
	console.log("ERROR! (3,2)+(4,5)=(", c3.re, ",", c3.im, ")");	
} 

if(nErrors==0) {
	console.log("OK");
}
