# -*- coding: utf-8 -*-
import numpy as np
from numpy import *
import serial

# port init
ser = serial.Serial()
ser.port = 'COM4'
ser.baudrate = 1200
ser.timeout = 0.1

# generate data
data = 'F024'
data = bytes.fromhex(data)
##data = bytearray(data, 'utf-8')

# write
ser.open()

for i in range(3):
    ser.write(data)
mm = ser.read(64)
mm = hex(int.from_bytes(mm, 'big'))
##mm = mm.decode()

print('returned:', mm)

ser.close()

