#!/usr/bin/python3

import math

points: int = 100

for i in range(0, points):
    angle = 2 * math.pi * i / points
    print("%d, " % (math.sin(angle) * 1000), end="")
