#include "trap.h"

void (*flash)(void) = (void (*)(void))0x30000000L;

int main(){
    flash();
}