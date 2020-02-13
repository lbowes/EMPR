import serial
import struct

import time
def write_screen(line):
    if len(line) > 16:
        print('16 or less only, champ')
        return
    if len(line)<16 :
        linee = line
        for i in range(0, 16-len(line)):
            linee += ' '
    ser.write(linee.encode())

def send_command(coord):
    values = []
    separated_coords = coord.split(',')

    for index in range (0,len(separated_coords)):
        sent_val = int (separated_coords[index])
        
        if sent_val > 255:
            sent_val = 255
        elif sent_val < -255:
            sent_val = -255
        print(sent_val)
        values.append(sent_val) 
    print(values)
    string = b''
    for i in values:
        if  i < 0:
            string += struct.pack('!B',1)
            string += struct.pack('!B',abs(i))
        else:
            string += struct.pack('!B',0)
            string += struct.pack('!B',i)
    ser.write(string)

    
ser = serial.Serial('/dev/ttyACM0')
ay = 'woah'


    



while ay != 'stop':
    ay = input()
    if ay != 'stop':
        send_command(ay)
        
#write_screen(ay)

ser.close


