//overloadOperators.js


var llFile = Polyglot.evalFile("llvm", "complex.so");
c1 = new llFile.Complex(3,2);
c2 = new llFile.Complex(4,5);
c3 = c1+c2;
console.log("(3,2)+(4,5)=(", c3.re, ",", c3.im, ")");

