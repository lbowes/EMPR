from tkinter import *
import serial
import struct
import time
import random


def read_RGB():
     run  = True
     while run:
         try:
             readline = ser.readline().decode("utf-8")
             
             #readline.remove('\r')

             if readline != 'start' and readline != 'running':


                 readline = readline.split()
                 print(readline)
                #  for o in readline:
                #      int(o)
                 #print("R" + readline[3])
                 #print("G" + readline[4])
                # print("B" + readline[5])
                 #print("C" + readline[6])    
                 
                 p = "(%s, %s), (%s, %s, %s, %s)" %(readline[0],readline[1],readline[3],readline[4],readline[5],readline[6])
                 file1.write(p + '\n')
                 
                 if readline[2] == 'ff':
                     print('done')
                     file1.close()
                     return 'finished'
                 elif len(readline) == 7:          
                     run = False
                     return readline
         except:
             pass
            





class command_entry:
    def __init__(self, frame, pos):
        self.box = Entry(frame, width = 8 )
        self.box.place(x = pos[0], y = pos[1])
        self.label = Label(frame, text = "x,y")
        self.label.place(x = pos[0], y = pos[1]+30)


    def clear_placeholder(self):
        self.box.delete(0, END)
    



class send_data_button:
    def __init__(self, frame, pos, entry_box):
        self.text = "send"
        self.pos = pos
        self.colour = 'blue'
        self.button = Button(frame, text = self.text ,bg = self.colour, command = lambda: self.press())
        self.button.place(x = pos[0], y = pos[1])
        self.entry_box = entry_box
        
    def press(self):
        values = []
        coord = self.entry_box.box.get()
        self.entry_box.box.delete(0,END)
        separated_coords = coord.split(',')
        print(separated_coords)
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
            print(sent_val)


        string = b''
        string += struct.pack('!B', 0x04)
        for i in values:
            string += struct.pack('!B',i)
        print(string)

        ser.write(string)





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
    




class quit_scan_button:
    def __init__(self, pos):
        self.text = 'Quit'
        self.pos = pos
        self.colour = 'red'
        self.Button = Button(root,bg = self.colour, text = self.text, command = lambda: self.press())
        self.Button.place (x = pos[0], y = pos[1])


    def press(self):
        pic_frame.delete('all')
        default()



class start_button:
    def __init__(self,frame, pos):
        self.text = "start scan"
        self.pos = pos
        self.colour  = "green"
        self.Button = Button(frame, text = self.text, 
			bg = self.colour, command = lambda: self.start_press())
        self.Button.place(x = pos[0], y = pos[1])
        


  

    def start_press(self):
        string = b''
        string += struct.pack('!B', 0x02)
        string += struct.pack('!B', 0x00)
        string += struct.pack('!B', 0x00)
        ser.write(string)
        pic_frame.delete('all')
        
        draw()







def run_now():
    col_val = read_RGB()
    if col_val == 'finished':
        default() 
    red = int(col_val[3], 16)
    print(red)
    green = int(col_val[4], 16)
    print(green)
    blue = int(col_val[5], 16)
    print(blue)
    clear_val = int(col_val[6], 16)
    grey = int(((red + green + blue) / 3))
    
    col_string = '#%02x%02x%02x' %(red, green ,blue )
    print(grey)
    pixel((col_val[0],(col_val[1])), col_string, pic_frame,5)
    
    #root.update()
    #root.after(1, run_now)

try:
    ser = serial.Serial('/dev/ttyACM0', baudrate = 460800)
except:
    try:
        ser = serial.Serial('/dev/ttyACM1', baudrate = 460800)
    except:
        print('port error')







root = Tk()
root.minsize(900,500)
root.title('TIME TO SCAN')

file1 = open("Coord_data.txt", "w")



pic_frame = Canvas(root, width = 450, height = 450,
                  bg = 'light grey', borderwidth = 5, relief = GROOVE )
pic_frame.place(x = 0, y = 0, anchor = NW)
uEntry = command_entry(root, (700,40))
entry_button = send_data_button(root, (700,0), uEntry)
#other_frame = Frame(root,width = 300, height = 300, bg = 'light grey')
#other_frame.grid(row = 0, column = 1, sticky = 'nsew')



start_button = start_button(root, (600,0))



#k = pixel((1,2), 'blue', 0)
#k1 = pixel((0,2), 'red', 0)


            
#k1 = pixel((0,0), '#00ff00', 0)
#k2 = pixel((1,0), '#ff0000', 0)
#root.after(0, run)
#root.mainloop()
#run_now()
def default ():
    while True:
        root.update_idletasks()
        root.update()

def draw():
    quit_button = quit_scan_button((600,50))
    while True:
        
        run_now()
        root.update_idletasks()
        root.update()

default()
#ser.close
#70, 70, 70, 200 white
#3,2,2,7  black

