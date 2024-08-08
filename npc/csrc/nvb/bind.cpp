#include <nvboard.h>
#include "VysyxSoCFull.h"

void nvboard_bind_all_pins(VysyxSoCFull* top) {
	nvboard_bind_pin( &top->externalPins_gpio_out, 16, LD15, LD14, LD13, LD12, LD11, LD10, LD9, LD8, LD7, LD6, LD5, LD4, LD3, LD2, LD1, LD0);
	nvboard_bind_pin( &top->externalPins_gpio_in, 16, SW15, SW14, SW13, SW12, SW11, SW10, SW9, SW8, SW7, SW6, SW5, SW4, SW3, SW2, SW1, SW0);
}
