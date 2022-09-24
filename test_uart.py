import serial
from threading import Timer
import time
import math

count = 0

def test_print():
        global count, t, com

        # if count == 1:
        #         msg = "1.0,2.0,3.0,30\n"
        #         count = 0
        # else:
        #         msg = "0,0,0,28\n"
        #         count = 1

        if count == 100:
                count = 0
        
        a = math.sin(count * 2 * math.pi /100) * 2
        b = math.sin(count * 2 * math.pi /100 + 2*math.pi/3) * 2
        c = math.sin(count * 2 * math.pi /100 + 2*math.pi/3*2) * 2

        msg = str(a) + ',' + str(b) + ',' + str(c) + ','
        msg += str(a) + ',' + str(b) + ',' + str(c) + '\n'

        count += 1
        
        com.write(msg.encode())
        t = Timer(0.02, test_print)
        t.start()

if __name__ == '__main__':
        com = serial.Serial('COM9', 115200)
        t = Timer(1, test_print)
        t.start()
        # msg = "a bc d"
        # com.write(msg.encode())

        # com.close()