#ifndef ENDIANNESS_H
#define ENDIANNESS_H

#include <stdint.h>

void swap_endianness_16bit(uint16_t *value);
void swap_endianness_32bit(uint32_t *value);

#endif
