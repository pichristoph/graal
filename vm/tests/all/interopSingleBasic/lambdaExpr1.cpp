//CPP
#include<polyglot.h>

int identity(int x) {
	return x;
}

class AClass {
	public:
		int (*foo)(int);
		AClass();
};

POLYGLOT_DECLARE_CLASS(AClass);

AClass::AClass() {
	foo = &identity;
}
