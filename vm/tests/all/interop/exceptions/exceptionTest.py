#exceptiontest.py

import polyglot

pyFile = polyglot.evalFile("py", "throwingProgram.py")

try:
	print("calculate 5/0: ")
	pyFile.run(5)
	print("This should not be printed.")
except:
	print("(Intentionally thrown) Exception has been caught")

llFile = polyglot.evalFile("llvm", "throwingProgram.so")

try:
	print("calculate 5/0: ")
	llFile.run(5)
	print("This should not be printed.")
except:
	print("(Intentionally thrown) Exception has been caught")
