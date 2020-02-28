from tkinter import *
import serial

import time
import random


def read_RGB():
     run  = True
     while run:
         try:
             readline = ser.readline().decode("utf-8")
             #readline.remove('\r')
             if readline != 'start' and readline != 'running':


                 readline = readline.split(' ')
                #  for o in readline:
                #      int(o)
                 #print("R" + readline[3])
                 #print("G" + readline[4])
                # print("B" + readline[5])
                 #print("C" + readline[6])    
                 if len(readline) == 7:          
                     run = False
                     return readline
         except:
             pass
            






class pixel:
    def __init__(self,pos,colour,canvas,size):
        self.posy = (int(pos[0], 16))*size
        self.posx = (int(pos[1], 16))*size
        self.size = size
        self.colour = colour
        self.canvas = canvas
        
        self.canvas.create_rectangle(self.posx, self.posy, self.posx +self.size, self.posy +self.size,fill = self.colour, outline = self.colour)
        #self.square = Frame(pic_frame, width = 5, height = 5, bg=self.colour)
        #self.frame.grid(row = pos[0], column = pos[1])
    






class start_button:
    def __init__(self,frame, pos):
        self.text = "start scan"
        self.pos = pos
        self.colour  = "green"
        self.Button = Button(frame, text = self.text, 
			bg = self.colour, command = lambda: self.start_press())
        self.Button.place(x = pos[0], y = pos[1])
        


  

    def start_press(self):
        ser.write(1)
        pic_frame.delete('all')
        
        #run_timer = 0
        #resolution = 45 * 50
        run_now()







def run_now():
    col_val = read_RGB()
    red = int(col_val[3], 16)
    print(red)
    green = int(col_val[4], 16)
    print(green)
    blue = int(col_val[5], 16)
    print(blue)

    col_string = '#%02x%02x%02x' %(red,green,blue)
    print(col_string)
    pixel((col_val[0],(col_val[1])), col_string, pic_frame,4)
    
    root.after(1, run_now)


ser = serial.Serial('/dev/ttyACM0')

root = Tk()
root.minsize(750,750)
root.title('TIME TO SCAN')






pic_frame = Canvas(root, width = 500, height = 500,
                  bg = 'light grey', borderwidth = 5, relief = GROOVE )
pic_frame.place(x = 0, y = 0, anchor = NW)

#other_frame = Frame(root,width = 300, height = 300, bg = 'light grey')
#other_frame.grid(row = 0, column = 1, sticky = 'nsew')



start_button = start_button(root, (600,0))



#k = pixel((1,2), 'blue', 0)
#k1 = pixel((0,2), 'red', 0)


            
#k1 = pixel((0,0), '#00ff00', 0)
#k2 = pixel((1,0), '#ff0000', 0)
#root.after(0, run)
root.mainloop()
#ser.close
#70, 70, 70, 200 white
#3,2,2,7  black

