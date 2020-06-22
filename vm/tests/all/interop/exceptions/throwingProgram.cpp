//throwingProgram.cpp

int run(int x) {
	if(x==0) {
		throw(x);
	} else {
		return x/0;
	}
}
