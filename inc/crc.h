#pragma once 

//---------------------------------------------------------

#include "modregs.h"

//=========================================================

#define CRC 0x40023000U

#define CRC_DR   (volatile uint32_t*)(uintptr_t)(CRC + 0x00)
#define CRC_IDR  (volatile uint32_t*)(uintptr_t)(CRC + 0x04)
#define CRC_CR   (volatile uint32_t*)(uintptr_t)(CRC + 0x08)
#define CRC_INIT (volatile uint32_t*)(uintptr_t)(CRC + 0x10)
#define CRC_POL  (volatile uint32_t*)(uintptr_t)(CRC + 0x14)

//---------------------------------------------------------

#define SET_CRC_IDR(value) PUPER_MODIFY_REG(CRC_IDR, value, 0xFF, 0)
#define GET_CRC_IDR() SUPER_CHECK_REG(CRC_IDR, 0xFF, 0)

//---------------------------------------------------------

#define CRC_CR_RESET 0

#define CRC_RESET() SET_BIT(CRC_CR, CRC_CR_RESET);

#define CRC_CR_POLYSIZE 3

#define CRC_CR_POLYSIZE_32 0b00
#define CRC_CR_POLYSIZE_16 0b01
#define CRC_CR_POLYSIZE_8  0b10
#define CRC_CR_POLYSIZE_7  0b11

#define SET_CR_POLYSIZE(value) PUPER_MODIFY_REG(CRC_CR, value, 0b11, CRC_CR_POLYSIZE)
#define GET_CR_POLYSIZE() SUPER_CHECK_REG(CRC_CR, 0b11, CRC_CR_POLYSIZE)

#define CRC_CR_REV_IN 5

#define CRC_CR_REV_IN_NONE 0b00
#define CRC_CR_REV_IN_B    0b01
#define CRC_CR_REV_IN_HW   0b10
#define CRC_CR_REV_IN_W    0b11

#define SET_CR_REV_IN(value) PUPER_MODIFY_REG(CRC_CR, value, 0b11, CRC_CR_REV_IN)
#define GET_CR_REV_IN() SUPER_CHECK_REG(CRC_CR, 0b11, CRC_CR_REV_IN)

#define CRC_CR_REV_OUT 7