//references.js

var llFile = Polyglot.evalFile("llvm", "references.so");

c = new llFile.MyClass();
c.i = 3;
ref = c.getRef();
ref = 4;

if(c.i==4) {
	console.log("OK");
} else {
	console.log("Error: 0 of 1 passed. c.i should be 4, but is ", c.i);
}
