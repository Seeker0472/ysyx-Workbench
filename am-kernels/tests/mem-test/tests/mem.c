#include "trap.h"

int main() {
	uint8_t test[8];
	for(volatile int i=0;i<8;i++){
		test[i]=(uint8_t)((uint32_t)(&test)&0xff);
	}
	for(volatile int i=0;i<8;i++){
		check(test[i]==(uint8_t)((uint32_t)(&test)&0xff));
	}

	return 0;
}
