import serial
from threading import Timer
import time

count = 0

def test_print():
        global count, t, com

        if count == 1:
                msg = "1.0,2.0,3.0,4.0\n"
                count = 0
        else:
                msg = "0,0,0,0\n"
                count = 1
        
        com.write(msg.encode())
        t = Timer(1, test_print)
        t.start()

if __name__ == '__main__':
        com = serial.Serial('COM9', 115200)
        t = Timer(1, test_print)
        t.start()
        # msg = "a bc d"
        # com.write(msg.encode())

        # com.close()