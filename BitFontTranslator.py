#!/usr/bin/python3

file = open("CP850-8x8.font", "rb")
data = file.read()

idx = 0

line = []

for byte in data:
    line.append(byte)
    idx += 1
    if (idx == 8):
        print("{", end="")
        
        for ch in range(len(line) - 1):
            val = line[ch]
            # val = int('{:08b}'.format(val)[::-1], 2)
            print(hex(val) + ", ", end="")
        
        val = line[-1]
        # val = int('{:08b}'.format(val)[::-1], 2)
        print(hex(val) + "},")
        
        line = []
        idx  = 0
