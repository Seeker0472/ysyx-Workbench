#include "../include/trap.h"

void __attribute__((optimize("O0"))) set(uint8_t* test) {
    for (volatile int i = 0; i < 100; i++) {
        test[i] = (uint8_t)((uint32_t)(&(test[i])) & 0xff);
    }
}

void __attribute__((optimize("O0"))) check_values(uint8_t* test) {
    for (volatile int i = 0; i < 100; i++) {
        check(test[i] == (uint8_t)((uint32_t)(&(test[i])) & 0xff));
    }
}

int main() {
    uint8_t test[1000];
    // uint8_t * test = malloc(100*sizeof(char));
    set(test);
    check_values(test);
    return 0;
}
