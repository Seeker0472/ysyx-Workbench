#include <stdint.h>

void init_pty();
void configure_pty_raw_mode();
void pty_write_byte(char c);
void pty_write_str(const char *str);
uint8_t pty_read_byte();
