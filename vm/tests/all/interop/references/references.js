//references.js

var llFile = Polyglot.evalFile("llvm", "referencesClass.so");

c = new llFile.MyClass();
c.i = 3;
ref = c.getRef();
ref = 4;
console.log("reference to c.i has been set to 4. c.i=",c.i);
