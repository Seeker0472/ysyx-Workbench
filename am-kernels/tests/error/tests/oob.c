#include "trap.h"

#pragma GCC diagnostic ignored "-Warray-bounds"

int arr[] = {0};


int main() {
	arr[1000000000000]=1;
	return 0;
}
