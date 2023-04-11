#pragma once 

//---------------------------------------------------------

#include "modregs.h"

//=========================================================

#define DMA 0x40020000U

#define DMA_ISR    (volatile uint32_t*)(uintptr_t)(DMA + 0x00)
#define DMA_IFCR   (volatile uint32_t*)(uintptr_t)(DMA + 0x04)

#define DMA_CCR1   (volatile uint32_t*)(uintptr_t)(DMA + 0x08)
#define DMA_CNDTR1 (volatile uint32_t*)(uintptr_t)(DMA + 0x0C)
#define DMA_CPAR1  (volatile uint32_t*)(uintptr_t)(DMA + 0x10)
#define DMA_CMAR1  (volatile uint32_t*)(uintptr_t)(DMA + 0x14)

#define DMA_CCR2   (volatile uint32_t*)(uintptr_t)(DMA + 0x1C)
#define DMA_CNDTR2 (volatile uint32_t*)(uintptr_t)(DMA + 0x20)
#define DMA_CPAR2  (volatile uint32_t*)(uintptr_t)(DMA + 0x24)
#define DMA_CMAR2  (volatile uint32_t*)(uintptr_t)(DMA + 0x28)

#define DMA_CCR3   (volatile uint32_t*)(uintptr_t)(DMA + 0x30)
#define DMA_CNDTR3 (volatile uint32_t*)(uintptr_t)(DMA + 0x34)
#define DMA_CPAR3  (volatile uint32_t*)(uintptr_t)(DMA + 0x38)
#define DMA_CMAR3  (volatile uint32_t*)(uintptr_t)(DMA + 0x3C)

#define DMA_CCR4   (volatile uint32_t*)(uintptr_t)(DMA + 0x44)
#define DMA_CNDTR4 (volatile uint32_t*)(uintptr_t)(DMA + 0x48)
#define DMA_CPAR4  (volatile uint32_t*)(uintptr_t)(DMA + 0x4C)
#define DMA_CMAR4  (volatile uint32_t*)(uintptr_t)(DMA + 0x50)

#define DMA_CCR5   (volatile uint32_t*)(uintptr_t)(DMA + 0x58)
#define DMA_CNDTR5 (volatile uint32_t*)(uintptr_t)(DMA + 0x5C)
#define DMA_CPAR5  (volatile uint32_t*)(uintptr_t)(DMA + 0x60)
#define DMA_CMAR5  (volatile uint32_t*)(uintptr_t)(DMA + 0x64)

//---------------------------------------------------------

// DMA interrupt status register

#define DMA_ISR_TEIF1 3
#define DMA_ISR_TEIF2 7
#define DMA_ISR_TEIF3 11
#define DMA_ISR_TEIF4 15
#define DMA_ISR_TEIF5 19

#define DMA_ISR_HTIF1 2
#define DMA_ISR_HTIF2 6
#define DMA_ISR_HTIF3 10
#define DMA_ISR_HTIF4 14
#define DMA_ISR_HTIF5 18

#define DMA_ISR_TCIF1 1
#define DMA_ISR_TCIF2 5
#define DMA_ISR_TCIF3 9
#define DMA_ISR_TCIF4 13
#define DMA_ISR_TCIF5 17

#define DMA_ISR_GIF1 0
#define DMA_ISR_GIF2 4
#define DMA_ISR_GIF3 8
#define DMA_ISR_GIF4 12
#define DMA_ISR_GIF5 16

//---------------------------------------------------------

// DMA interrupt flag clear register

#define DMA_ISR_CTEIF1 3
#define DMA_ISR_CTEIF2 7
#define DMA_ISR_CTEIF3 11
#define DMA_ISR_CTEIF4 15
#define DMA_ISR_CTEIF5 19

#define DMA_ISR_CHTIF1 2
#define DMA_ISR_CHTIF2 6
#define DMA_ISR_CHTIF3 10
#define DMA_ISR_CHTIF4 14
#define DMA_ISR_CHTIF5 18

#define DMA_ISR_CTCIF1 1
#define DMA_ISR_CTCIF2 5
#define DMA_ISR_CTCIF3 9
#define DMA_ISR_CTCIF4 13
#define DMA_ISR_CTCIF5 17

#define DMA_ISR_CGIF1 0
#define DMA_ISR_CGIF2 4
#define DMA_ISR_CGIF3 8
#define DMA_ISR_CGIF4 12
#define DMA_ISR_CGIF5 16

//---------------------------------------------------------

// DMA channel x configuration register

#define DMA_CCR_EN    0
#define DMA_CCR_TCIE  1
#define DMA_CCR_HTIE  2
#define DMA_CCR_TEIE  3
#define DMA_CCR_DIR   4 // 0 - read from peripheral, 1 - read from memory
#define DMA_CCR_CIRC  5
#define DMA_CCR_PINC  6
#define DMA_CCR_MINC  7

#define DMA_CCR_PSIZE 8

#define DMA_CCR_PSIZE_8  0b00
#define DMA_CCR_PSIZE_16 0b01
#define DMA_CCR_PSIZE_32 0b10

#define SET_DMA_CCR_PSIZE(REG, value) PUPER_MODIFY_REG(REG, 0b11, value, DMA_CCR_PSIZE)
#define GET_DMA_CCR_PSIZE(REG) SUPER_CHECK_REG(REG, 0b11, DMA_CCR_PSIZE)

#define DMA_CCR_MSIZE 10

#define DMA_CCR_MSIZE_8  0b00
#define DMA_CCR_MSIZE_16 0b01
#define DMA_CCR_MSIZE_32 0b10

#define SET_DMA_CCR_MSIZE(REG, value) PUPER_MODIFY_REG(REG, 0b11, value, DMA_CCR_MSIZE)
#define GET_DMA_CCR_MSIZE(REG) SUPER_CHECK_REG(REG, 0b11, DMA_CCR_MSIZE)

#define DMA_CCR_PL 12

#define DMA_CCR_PL_LOW       0b00
#define DMA_CCR_PL_MED       0b01
#define DMA_CCR_PL_HIGH      0b10
#define DMA_CCR_PL_VERY_HIGH 0b11

#define SET_DMA_CCR_PL(REG, value) PUPER_MODIFY_REG(REG, 0b11, value, DMA_CCR_PL)
#define GET_DMA_CCR_PL(REG) SUPER_CHECK_REG(REG, 0b11, DMA_CCR_PL)

#define DMA_CCR_MEM2MEM 14

//---------------------------------------------------------

// DMA channel x number of data register

#define DMA_CNDTR_NDT 0

#define SET_DMA_CNDTR_NDT(REG, value) PUPER_MODIFY_REG(REG, 0xFFFF, value, DMA_CNDTR_NDT)
#define GET_DMA_CNDTR_NDT(REG) SUPER_CHECK_REG(REG, 0xFF, DMA_CNDTR_NDT)

//---------------------------------------------------------

// DMA channel x peripheral address register

#define SET_DMA_CPAR(REG, value) (*(REG) = value)
#define GET_DMA_CPAR(REG) (*(REG))

//---------------------------------------------------------

// DMA channel x memory address register

#define SET_DMA_CMAR(REG, value) (*(REG) = value)
#define GET_DMA_CMAR(REG) (*(REG))
