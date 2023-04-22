# LoadPlatform 
This project is being developed as part of the course on microcontrollers at MIPT DREC 2 course 4 semester 2022-2023. The project was implemented WITHOUT the use of third-party libraries.

---

### Brief description
In order to run new code on the microcontroller, it is necessary to overwrite the flash memory, which has a limited number of overwrites.

STgaMe32 is host hardware and peripherals, that allows you to run guest code without having to rewrite flash. The host firmware also provides a certain interface of useful functions for interacting with peripherals.

<!-- ## Plan
 - Implement UART driver with DMA support
 - Develop API for guest user programs (for games basically)
 - Add guest program start-up code
 - Add support for OLED display over SPI and some controls (e.g. buttons)
 - Make a test program - simple game. -->

---

### Installation & Usage

 - Clone repository 
 - Install necessary python modules
 - use 'make flash' to load host software to mc
 - use 'USRC=\<src> make ucode' to load guest code 

![Example of working device](https://github.com/k-kashapov/LoadPlatform/blob/main/IMG.jpg)

---

### Project build peripherals

 - 4 simple buttons used for controls 
 - UART-to-USB adapter to receive binaries from computer
 - STM32F0DISCOVERY board
 - Connection wires & bread board
 - USB-to-mini USB adapter to power up the microcontroller 
 - SSD1306 OLED display

### Host initialization
Host initialization involves several steps:

 - board clock initialization: APB & AHB frequency - 48Mhz 
 - systick timer initialization with a period of 100 µs
 - additional initialization of the code module responsible for providing API functions to the guest code
 - OLED display via SPI initialization

### Receiving guest code
The microcontroller receives the user code via USART. The code is placed in a fixed area of memory in SRAM, from where it will be executed. In order not to load the processor in the process of receiving the code, USART uses DMA. The firmware expects the maximum allowed binary file size. However, if there is a delay in receiving within 1.5 seconds, the receiving will stop and the firmware will switch to running the code.

Bit parity checks, as well as overrun and noise detection checks are used to ensure that the integrity of user code is not corrupted upon receipt. In addition, when sending, the crc32 hash from the sent binary file is calculated and appended to the end of the sent packet. Еhe receiving side uses the crc counting support on the microcontroller to compare the received value with the newly calculated one. Received code will not be executed if the hash values do not match.

---

### Guest code's launch
After the initial initialization of the firmware and receiving the guest code, the firmware runs the user code, starting with the umain function. This function is used by the linker script as an entry point, so it must be present in the resulting code. The umain function takes as an argument a pointer to a structure representing the firmware API.

The structure contains pointers to functions that are in flash memory and are part of the firmware. The structure itself, as well as other objects necessary for the implementation of the API, are in the SRAM area, which is reserved for use by the firmware. 

---

### API 
Among the features provided by the API: control over two diodes, reading the status from four buttons (pressed / not pressed), access to the screen with the ability to draw in bw.
