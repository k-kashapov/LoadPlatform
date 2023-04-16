#pragma once 

//=========================================================

#include <stdint.h>

//=========================================================

void crc_init(uint32_t init);
uint32_t crc32_calc(uint8_t* data, size_t size);