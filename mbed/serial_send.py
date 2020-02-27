import serial
import struct

import time





def read_RGB():
    run  = True
    while run:
        try:
            readline= ser.readline().decode("utf-8")
            if readline != 'start' and readline != 'running':
                readline = readline[6:]
                readline = readline.split(' ')
                print("R " + readline[0])
                print("G " + readline[1])
                print("B " + readline[2])
                print("C " + readline[3])                
                run = False
        except:
            pass




def move_to_coords(coord):
    
    values = []
    separated_coords = coord.split(',')

    for index in range (0,2):
        try:
            sent_val = int (separated_coords[index])
        except ValueError:
            print("numbers only you monster")
            return 
        
        if sent_val > 200:
            sent_val = 200
        elif sent_val < 0:
            sent_val = 0
        
        values.append(sent_val) 

    string = b''

    for i in values:
        string += struct.pack('!B',i)

    ser.write(string)



#not used, reference only
def send_command_relative(coord):
    values = []
    separated_coords = coord.split(',')

    for index in range (0,len(separated_coords)):
        sent_val = int (separated_coords[index])
        
        if sent_val > 255:
            sent_val = 255
        elif sent_val < -255:
            sent_val = -255
        values.append(sent_val) 

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



    
ay = "aha"


while ay != 'stop':
    #ay = input()
    if ay != 'stop':
        #move_to_coords(ay)
        read_RGB()
        
#write_screen(ay)

ser.close


