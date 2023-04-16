#!/usr/bin/python3

#=========================================================

import serial
import sys
import crcmod
import zlib

#=========================================================

def serial_init(speed):
    dev = serial.Serial(
        port     = '/dev/ttyUSB0', 
        baudrate = speed,
        parity   = serial.PARITY_ODD,
        stopbits = serial.STOPBITS_ONE,
        bytesize = serial.EIGHTBITS,
        timeout  = 3
    )
    return dev

#---------------------------------------------------------

def serial_recv_str(dev):
    # Для простоты макс. кол-во символов для чтения - 255. Время ожидания - 0.1
    # decode необходим для конвертирования набора полученных байтов в строку
    string = dev.read(255).decode()
    return string

#---------------------------------------------------------

def serial_send_str(dev, string):
    # encode конвертирует строку в кодировке utf-8 в набор байтов 
    dev.write(string.encode('utf-8'))

#---------------------------------------------------------

def serial_recv(dev):
    return dev.read(255)

#---------------------------------------------------------

def serial_send(dev, data):
    dev.write(data)

#=========================================================

if len(sys.argv) != 2:
    print("Usage: sudo ./usart.py /path/to/binary")

binary_data = [] 

with open(sys.argv[1], mode='rb') as binary:
    
    binary_data = binary.read() # read binary file to send
    print(binary_data)

    hash = zlib.crc32(binary_data)
    print(hex(hash))

    while (len(binary_data) % 4) != 0:
        binary_data += b'\0' # append zero bytes for word alignment

    binary_data += hash.to_bytes(4, "little")
    # print(binary_data) 

    dev = serial_init(9600) 
    serial_send(dev, binary_data)

