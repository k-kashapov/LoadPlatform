# STgaMe32 

This project is being developed as part of the course on microcontrollers at MIPT DREC 2 course 4 semester 2022-2023 in collaboration with Kamil Kashapov(github: [k-kashapov](https://github.com/k-kashapov))

## Plan
 - Implement UART driver with DMA support
 - Develop API for guest user programs (for games basically)
 - Add guest program start-up code
 - Add support for OLED display over SPI and some controls (e.g. buttons)
 - Make a test program - simple game. For example, Tetris

## Current state

 - UART & DMA - **done** 
 - Tetris: game's 'model' is done, we need to implement new 'view' for it
 - SPI support implemented

## Hardware peripherals

 - 4 simple buttons used for controls 
 - UART-to-USB adapter to receive binaries from computer
 - STM32F0DISCOVERY board
 - Connection wires & bread board
 - USB-to-mini USB adapter to power up the microcontroller 
 - SSD1306 OLED display