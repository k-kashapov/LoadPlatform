#ifndef GENERAL_H
#define GENERAL_H

#include <stdint.h>

#define BIT_SET(REG, BIT)   do (REG) |=  (1U << (BIT)); while(0)
#define BIT_CLR(REG, BIT)   do (REG) &= ~(1U << (BIT)); while(0)
#define BIT_INV(REG, BIT)   do (REG) ^=  (1U << (BIT)); while(0)
#define BIT_READ(REG, BIT)  (REG & (1U << (BIT)))

#define MASK_LOWER(WIDTH) ((1U << (WIDTH)) - 1)

#define FIELD_WRITE(REG, VALUE, SHIFT) ((REG) |= ((VALUE) << (SHIFT)))
#define FIELD_READ(REG, MASK)          ((REG) & (MASK))

#endif // GENERAL_H