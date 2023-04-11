#pragma once 

//---------------------------------------------------------

#include "modregs.h"

//=========================================================

#define USART1 0x40013800
#define USART2 0x40004400
#define USART3 0x40004800
#define USART4 0x40004C00
#define USART5 0x40005000
#define USART6 0x40011400
#define USART7 0x40011800
#define USART8 0x40011C00

//---------------------------------------------------------

#define USART_CR1(USARTx)  (volatile uint32_t*)(uintptr_t)(USARTx + 0x00)
#define USART_CR2(USARTx)  (volatile uint32_t*)(uintptr_t)(USARTx + 0x04)
#define USART_CR3(USARTx)  (volatile uint32_t*)(uintptr_t)(USARTx + 0x08)
#define USART_BRR(USARTx)  (volatile uint32_t*)(uintptr_t)(USARTx + 0x0C)
#define USART_GTPR(USARTx) (volatile uint32_t*)(uintptr_t)(USARTx + 0x10)
#define USART_RTOR(USARTx) (volatile uint32_t*)(uintptr_t)(USARTx + 0x14)
#define USART_RQR(USARTx)  (volatile uint32_t*)(uintptr_t)(USARTx + 0x18)
#define USART_ISR(USARTx)  (volatile uint32_t*)(uintptr_t)(USARTx + 0x1C)
#define USART_ICR(USARTx)  (volatile uint32_t*)(uintptr_t)(USARTx + 0x20)
#define USART_RDR(USARTx)  (volatile uint32_t*)(uintptr_t)(USARTx + 0x24)
#define USART_TDR(USARTx)  (volatile uint32_t*)(uintptr_t)(USARTx + 0x28)

//---------------------------------------------------------

// Control register 1

#define USART_CR1_UE     0  // USART enable
#define USART_CR1_UESM   1  // USART enable in Stop mode
#define USART_CR1_RE     2  // Receiver enable
#define USART_CR1_TE     3  // Transmitter enable
#define USART_CR1_IDLEIE 4  // IDLE interrupt enable
#define USART_CR1_RXNEIE 5  // RXNE interrupt enable
#define USART_CR1_TCIE   6  // Transmission complete interrupt enable
#define USART_CR1_TXEIE  7  // TXE interrupt enable
#define USART_CR1_PEIE   8  // PE interrupt enable
#define USART_CR1_PS     9  // Parity selection
#define USART_CR1_PCE    10 // Parity control enable
#define USART_CR1_WAKE   11 // Receiver wakeup method
#define USART_CR1_M0     12 // Word length
#define USART_CR1_MME    13 // Mute mode enable 
#define USART_CR1_CMIE   14 // Character match interrupt enable
#define USART_CR1_OVER8  15 // Oversampling mode
#define USART_CR1_DEDT   16 // Driver Enable de-assertion time

#define SET_USART_CR1_DEDT(USARTx, value) SUPER_MODIFY_REG(USART_CR1(USARTx), 0b11111, value, USART_CR1_DEDT)
#define GET_USART_CR1_DEDT(USARTx) SUPER_CHECK_REG(USART_CR1(USARTx), 0b11111, USART_CR1_DEDT)

#define USART_CR1_DEAT   21 // Driver Enable assertion time

#define SET_USART_CR1_DEAT(USARTx, value) SUPER_MODIFY_REG(USART_CR1(USARTx), 0b11111, value, USART_CR1_DEAT)
#define GET_USART_CR1_DEAT(USARTx) SUPER_CHECK_REG(USART_CR1(USARTx), 0b11111, USART_CR1_DEAT)

#define USART_CR1_RTOIE  26 // Receiver timeout interrupt enable
#define USART_CR1_EOBIE  27 // End of Block interrupt enable
#define USART_CR1_M1     28 // Word length

//---------------------------------------------------------

// Control register 2

#define USART_CR2_ADDM7 4  // 7-bit Address Detection/4-bit Address Detection
#define USART_CR2_LBDL  5  // LIN break detection length
#define USART_CR2_LBDIE 6  // LIN break detection interrupt enable
#define USART_CR2_LBCL  8  // Last bit clock pulse
#define USART_CR2_CPHA  9  // Clock phase
#define USART_CR2_CPOL  10 // Clock polarity
#define USART_CR2_CLKEN 11 // Clock enable
#define USART_CR2_STOP  12 // STOP bits

#define USART_CR2_STOP_1   0b00
#define USART_CR2_STOP_0_5 0b01
#define USART_CR2_STOP_2   0b10
#define USART_CR2_STOP_1_5 0b11

#define SET_USART_CR2_STOP(USARTx, value) SUPER_MODIFY_REG(USART_CR2(USARTx), 0b11, value, USART_CR2_STOP)
#define GET_USART_CR2_STOP(USARTx) SUPER_CHECK_REG(USART_CR2(USARTx), 0b11, USART_CR2_STOP)

#define USART_CR2_LINEN    14 // LIN mode enable
#define USART_CR2_SWAP     15 // Swap TX/RX pins
#define USART_CR2_RXINV    16 // RX pin active level inversion
#define USART_CR2_TXINV    17 // TX pin active level inversion
#define USART_CR2_DATAINV  18 // Binary data inversion
#define USART_CR2_MSBFIRST 19 // Most significant bit first 
#define USART_CR2_ABREN    20 // Auto baud rate enable
#define USART_CR2_ABRMOD   21 // Auto baud rate mode

#define USART_CR2_ABRMOD_MEAS_START_BIT  0b00
#define USART_CR2_ABRMOD_FE_TO_FE_MEAS   0b01
#define USART_CR2_ABRMOD_0x7F_FRM_DETECT 0b10
#define USART_CR2_ABRMOD_0x55_FRM_DETECT 0b11

#define SET_USART_CR2_ABRMOD(USARTx, value) SUPER_MODIFY_REG(USART_CR2(USARTx), 0b11, value, USART_CR2_ABRMOD)
#define GET_USART_CR2_ABRMOD(USARTx) SUPER_CHECK_REG(USART_CR2(USARTx), 0b11, USART_CR2_ABRMOD)

#define USART_CR2_RTOEN 23 // Receiver timeout enable
#define USART_CR2_ADD   24 // Address of the USART node

#define SET_USART_CR2_ADD(USARTx, value) SUPER_MODIFY_REG(USART_CR2(USARTx), 0b11111111, value, USART_CR2_ADD)
#define GET_USART_CR2_ADD(USARTx) SUPER_CHECK_REG(USART_CR2(USARTx), 0b11111111, USART_CR2_ADD)        

//---------------------------------------------------------

// Control register 3

#define USART_CR3_EIE     0  // Error interrupt enable
#define USART_CR3_IREN    1  // IrDA mode enable
#define USART_CR3_IRLP    2  // IrDA low-power
#define USART_CR3_HDSEL   3  // Half-duplex selection
#define USART_CR3_NACK    4  // Smartcard NACK enable
#define USART_CR3_SCEN    5  // Smartcard mode enable
#define USART_CR3_DMAR    6  // DMA enable receiver
#define USART_CR3_DMAT    7  // DMA enable transmitter
#define USART_CR3_RTSE    8  // RTS enable
#define USART_CR3_CTSE    9  // CTS enable
#define USART_CR3_CTSIE   10 // CTS interrupt enable
#define USART_CR3_ONEBIT  11 // One sample bit method enable
#define USART_CR3_OVRDIS  12 // Overrun Disable
#define USART_CR3_DDRE    13 // DMA Disable on Reception Error
#define USART_CR3_DEM     14 // Driver enable mode
#define USART_CR3_DEP     15 // Driver enable polarity selection
#define USART_CR3_SCAPCNT 17 // Smartcard auto-retry count

#define SET_USART_CR3_SCAPCNT(UARTx, value) SUPER_MODIFY_REG(USART_CR3(USARTx), 0b111, value, USART_CR3_SCAPCNT)
#define GET_USART_CR3_SCAPCNT(UARTx) SUPER_CHECK_REG(USART_CR3(USARTx), 0b111, USART_CR3_SCAPCNT)

#define USART_CR3_WUS 20 // Wakeup from Stop mode interrupt flag selection

#define USART_CR3_WUS_ACTIVE_ADD_MATCH 0b00
#define USART_CR3_WUS_ACTIVE_START_BIT 0b10
#define USART_CR3_WUS_ACTIVE_RXNE      0b11

#define SET_USART_CR3_WUS(UARTx, value) SUPER_MODIFY_REG(USART_CR3(USARTx), 0b11, value, USART_CR3_WUS)
#define GET_USART_CR3_WUS(UARTx) SUPER_CHECK_REG(USART_CR3(USARTx), 0b11, USART_CR3_WUS)

#define USART_CR3_WUFIE 22 // Wakeup from Stop mode interrupt enable

//---------------------------------------------------------

// Baud rate register 

#define USART_BRR_HIGH_12 4

#define SET_USART_BRR_HIGH_12(USARTx, value) SUPER_MODIFY_REG(USART_BRR(USARTx), 0b111111111111, value, USART_BRR_BRR_HIGH_12)
#define GET_USART_BRR_HIGH_12(USARTx) SUPER_MODIFY_REG(USART_BRR(USARTx), 0b111111111111, USART_BRR_BRR_HIGH_12)

#define USART_BRR_LOW_4   0

#define SET_USART_BRR_LOW_4(USARTx, value) SUPER_MODIFY_REG(USART_BRR(USARTx), 0b1111, value, USART_BRR_BRR_LOW_4)
#define GET_USART_BRR_LOW_4(USARTx) SUPER_MODIFY_REG(USART_BRR(USARTx), 0b1111, USART_BRR_BRR_LOW_4)

#define SET_USART_BRR(USARTx, value) SUPER_MODIFY_REG(USART_BRR(USARTx), 0xFFFF, value, 0)
#define GET_USART_BRR(USARTx) SUPER_CHECK_REG(USART_BRR(USARTx), 0xFFFF, 0)
//---------------------------------------------------------

// Guard time and prescaler register

#define USART_GTPR_PSC 0 // Prescaler value

#define SET_USART_GTPR_PSC(USARTx, value) SUPER_MODIFY_REG(USART_GTPR(USARTx), 0b11111111, value, USART_GTPR_PSC)
#define GET_USART_GTPR_PSC(USARTx) SUPER_CHECK_REG(USART_GTPR(USARTx), 0b11111111, USART_GTPR_PSC)

#define USART_GTPR_GT 8 // Guard time value

#define SET_USART_GTPR_GT(USARTx, value) SUPER_MODIFY_REG(USART_GTPR(USARTx), 0b11111111, value, USART_GTPR_GT)
#define GET_USART_GTPR_GT(USARTx) SUPER_CHECK_REG(USART_GTPR(USARTx), 0b11111111, USART_GTPR_GT)

//---------------------------------------------------------

// Receiver timeout register

#define USART_RTOR_RTO 0 // Receiver timeout value

#define SET_USART_RTOR_RTO(USARTx, value) SUPER_MODIFY_REG(USART_RTOR(USARTx), 0xFFFFFF, value, USART_RTOR_RTO)
#define GET_USART_RTOR_RTO(USARTx) SUPER_CHECK_REG(USART_RTOR(USARTx), 0xFFFFFF, USART_RTOR_RTO)

#define USART_RTOR_BLEN 24 // Block Length

#define SET_USART_RTOR_BLEN(USARTx, value) SUPER_MODIFY_REG(USART_RTOR(USARTx), 0b11111111, value, USART_RTOR_BLEN)
#define GET_USART_RTOR_BLEN(USARTx) SUPER_CHECK_REG(USART_RTOR(USARTx), 0b11111111, USART_RTOR_BLEN)

//---------------------------------------------------------

// Request register

#define USART_RQR_ABRRQ 0 // Auto baud rate request
#define USART_RQR_SBKRQ 1 // Send break request
#define USART_RQR_MMRQ  2 // Mute mode request
#define USART_RQR_RXFRQ 3 // Receive data flush request
#define USART_RQR_TXFRQ 4 // Transmit data flush reques

//---------------------------------------------------------

// Interrupt and status register

#define USART_ISR_PE    0  // Parity error
#define USART_ISR_FE    1  // Framing error
#define USART_ISR_NF    2  // START bit Noise detection flag
#define USART_ISR_ORE   3  // Overrun error
#define USART_ISR_IDLE  4  // Idle line detected
#define USART_ISR_RXNE  5  // Read data register not empty
#define USART_ISR_TC    6  // Transmission complete
#define USART_ISR_TXE   7  // Transmit data register empty 
#define USART_ISR_LBDF  8  // LIN break de tection flag
#define USART_ISR_CTSIF 9  // CTS interrupt flag 
#define USART_ISR_CTS   10 // CTS flag
#define USART_ISR_RTOF  11 // Receiver timeot
#define USART_ISR_EOBF  12 // End of block flag
#define USART_ISR_ABRE  14 // Auto baud rate error
#define USART_ISR_ABRF  15 // Auto baud rate flag
#define USART_ISR_BUSY  16 // Busy flag
#define USART_ISR_CMF   17 // Character match flag
#define USART_ISR_SBKF  18 // Send break flag
#define USART_ISR_RWU   19 // Receiver wakeup from Mute mode
#define USART_ISR_WUF   20 // Wakeup from Stop mode flag
#define USART_ISR_TEACK 21 // Transmit enable acknowledge flag
#define USART_ISR_REACK 22 // Receive enable acknowledge flag

//---------------------------------------------------------

// Interrupt flag clear register

#define USART_ICR_PECF   0  // Parity error
#define USART_ICR_FECF   1  // Framing error
#define USART_ICR_NFCF   2  // START bit Noise detection flag
#define USART_ICR_ORECF  3  // Overrun error
#define USART_ICR_IDLECF 4  // Idle line detected
#define USART_ICR_TCCF   6  // Transmission complete
#define USART_ICR_LBDCF  8  // LIN break de tection flag
#define USART_ICR_CTSICF 9  // CTS interrupt flag 
#define USART_ICR_RTOCF  11 // Receiver timeot
#define USART_ICR_EOBCF  12 // End of block flag
#define USART_ICR_CMCF   17 // Character match flag
#define USART_ICR_WUCF   20 // Wakeup from Stop mode flag

//---------------------------------------------------------

// Receive data register

#define GET_USART_RDR(USARTx) SUPER_CHECK_REG(USART_RDR(USARTx), 0b111111111, 0)

//---------------------------------------------------------

// Transmit data register 

#define SET_USART_TDR(USARTx, value) SUPER_MODIFY_REG(USART_TDR(USARTx), 0b111111111, value, 0)
#define GET_USART_TDR(USARTx) SUPER_CHECK_REG(USART_TDR(USARTx), 0b111111111, 0)

