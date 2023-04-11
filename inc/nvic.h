#pragma once 

//---------------------------------------------------------

#include "modregs.h"

//=========================================================

// Nested Vectored Interrupt Controller

#define NVIC_ISER (volatile uint32_t*)(uintptr_t)0xE000E100U // RW - Interrupt Set-enable Register
#define NVIC_ICER (volatile uint32_t*)(uintptr_t)0xE000E180U // RW - Interrupt Clear-enable Register
#define NVIC_ISPR (volatile uint32_t*)(uintptr_t)0xE000E200U // RW - Interrupt Set-pending Register
#define NVIC_ICPR (volatile uint32_t*)(uintptr_t)0xE000E280U // RW - Interrupt Clear-pending Register

#define NVIC_IPR0 (volatile uint32_t*)(uintptr_t)0xE000E400U // RW - Interrupt Priority Register 0
#define NVIC_IPR1 (volatile uint32_t*)(uintptr_t)0xE000E404U // RW - Interrupt Priority Register 1
#define NVIC_IPR2 (volatile uint32_t*)(uintptr_t)0xE000E408U // RW - Interrupt Priority Register 2
#define NVIC_IPR3 (volatile uint32_t*)(uintptr_t)0xE000E40CU // RW - Interrupt Priority Register 3
#define NVIC_IPR4 (volatile uint32_t*)(uintptr_t)0xE000E410U // RW - Interrupt Priority Register 4
#define NVIC_IPR5 (volatile uint32_t*)(uintptr_t)0xE000E414U // RW - Interrupt Priority Register 5
#define NVIC_IPR6 (volatile uint32_t*)(uintptr_t)0xE000E418U // RW - Interrupt Priority Register 6
#define NVIC_IPR7 (volatile uint32_t*)(uintptr_t)0xE000E41CU // RW - Interrupt Priority Register 7

//---------------------------------------------------------

#define NVIC_ENABLE_IRQ(irq_no) (*(NVIC_ISER) = (1 << irq_no))
#define NVIC_DISABLE_IRQ(irq_no) (*(NVIC_ICER) = (1 << irq_no))

#define NVIC_SET_PEND_IRQ(irq_no) (*(NVIC_ISPR) = (1 << irq_no))
#define NVIC_CLEAR_PEND_IRQ(irq_no) (*(NVIC_ICPR) = (1 << irq_no))

//---------------------------------------------------------

#define NVIC_IS_ENABLE_IRQ(irq_no) CHECK_BIT(NVIC_ISER, irq_no)
#define NVIC_IS_PEND_IRQ(irq_no) CHECK_BIT(NVIC_ISPR, irq_no)
 