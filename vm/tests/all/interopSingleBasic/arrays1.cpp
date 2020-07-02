//CPP
#include<polyglot.h>

void* getSquaredArray(int n) {
	int arr[n];
	for(int i=0;i<n;i++) {
		arr[i] = i*i;
	}
	void* ret = polyglot_from_i64_array(arr, n);
	return ret;
}


