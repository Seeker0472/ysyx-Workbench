#include "trap.h"

void set(uint8_t* test) {
    for (volatile int i = 0; i < 8; i++) {
        test[i] = (uint8_t)((uint32_t)(&(test[i])) & 0xff);
    }
}

void __attribute__((optimize("O0"))) check_values(uint8_t* test) {
    for (volatile int i = 0; i < 8; i++) {
        check(test[i] == (uint8_t)((uint32_t)(&(test[i])) & 0xff));
    }
}

int main() {
    uint8_t test[8];
    set(test);
    check_values(test);
    return 0;
}
