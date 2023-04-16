#include <stdlib.h>
#include <stdbool.h>

//---------------------------------------------------------

#include "inc/gpio.h"
#include "inc/crc.h"
#include "inc/rcc.h"
#include "crc.h"

//=========================================================

void crc_init(uint32_t init)
{
    *CRC_INIT = init;
}


uint32_t crc32_calc(uint8_t* data, size_t size)
{
    SET_BIT(REG_RCC_AHBENR, REG_RCC_AHBENR_CRCEN);
    SET_CR_REV_IN(CRC_CR_REV_IN_W);
    SET_BIT(CRC_CR, CRC_CR_REV_OUT);

    CRC_RESET();

    uint32_t ind = 0;
    uint32_t full_word_bytes = size & 0b11;

    while (ind < full_word_bytes) 
    {
        *CRC_DR = *(uint32_t*)&data[ind];
        ind += 4;
    }

    while (ind < size) 
    {
        *(uint8_t*)(CRC_DR) = data[ind];
        ind++;
    }

    uint32_t res = *CRC_DR ^ 0xFFFFFFFF;
    CLEAR_BIT(REG_RCC_AHBENR, REG_RCC_AHBENR_CRCEN);
    
    return res;
}
