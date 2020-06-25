#exceptiontest

import polyglot

pyFile = polyglot.evalFile("py", "throwingProgram.py")
passed=0
try:
	pyFile.run(5)	#calculate 5/0
	print("This should not be printed. (Planned) exception has not been thrown.")
except:
	passed++	#Intentionally thrown Exception has been caught

llFile = polyglot.evalFile("llvm", "throwingProgram.so")

try:
	llFile.run(5)	#calculate 5/0
	print("This should not be printed. (Planned) exception has not been thrown.")
except:
	passed++	#Intentionally thrown Exception has been caught

if(passed==2):
	print("OK")
else:
	print("ERROR. Passed: ", passed, " of 2.")
