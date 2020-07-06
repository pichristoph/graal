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

void* evaluate(void* aClass, void* argument) {
	AClass* aObj = polyglot_as_AClass(aClass);
	int64_t val = polyglot_as_int64(argument);
	int64_t returnValue = (*(aObj->foo))(val);
	void* returnObj = polyglot_from_int64(returnValue);
	free(aObj);
	return returnObj;
}
