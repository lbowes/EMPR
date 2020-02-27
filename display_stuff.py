import tkinter
import serial
import struct
import time



def read_RGB():
    run  = True
    while run:
        try:
            #print('milk')
            readline = ser.readline().decode("utf-8")
            #print('ayo')
            if readline != 'start' and readline != 'running':
                print(readline)
                #readline = readline[6:]
                readline = readline.split(' ')
                #print("R" + readline[3])
                #print("G" + readline[4])
                #print("B" + readline[5])
                #print("C" + readline[6])    
                if len(readline) == 7:          
                    run = False
                    return readline
        except:
            pass
            






class pixel:
    def __init__(self,pos,colour,next):
        #print('veryken')
        self.pos = pos
        self.colour = colour
        self.frame = tkinter.Frame(width = 20, height = 20, bg=self.colour)
        self.frame.grid(row = pos[0], column = pos[1])
    




    def press(self):
        print(self.colour)
        print(self.pos)



# def run():
#     for rows in range(0,50):
#     for columns in range(0,50):
#         col_val = read_RGB()
#         #print('help')
#         if int(col_val[6]) < 100:
#             print('yes')
#             pixel((rows,columns), "black",0)
#         else:
#             pixel((rows,columns), "white",0)

def run():
    col_val = read_RGB()
    print('help')
    if int(col_val[6]) < 100 :
        print('jello')
        pixel((col_val[0],(col_val[1])), "black",0)
    else:
        print('jksdfsg')
        pixel((col_val[0],col_val[1]), "white",0)
    root.after(1,run)
    

ser = serial.Serial('/dev/ttyACM0')

root = tkinter.Tk()

# frame = tkinter.Button(root,width=4, height=2, bg="red",command=lambda: print_rgb)
# frame.grid(row=0,column=0)
# frame = tkinter.Button(root,width=4, height=2, bg="blue")
# frame.grid(row=1,column=0)
# frame = tkinter.Button(root,width=4, height=2, bg="blue")
# frame.grid(row=1,column=2)

#k = pixel((1,2), 'blue', 0)
#k1 = pixel((0,2), 'red', 0)


            
#k1 = pixel((30,30), 'green', 0)

root.after(5, run())
root.mainloop()
ser.close
#70, 70, 70, 200 white
#3,2,2,7  black

