# Get from the lib tkinter
from tkinter import *
# Serial line
import serial
# Time
import time

# TODO remove me
import random


# Global States




# Returns RGB
def read_RGBAndPos():
    run = True
    while run:
        try:
            #  Decode readline
            #  readline = ser.readline().decode("utf-8")
            #  TODO remove me
            readline = f"{hex(random.choice(range(0,100)))[2:]} {hex(random.choice(range(0,100)))[2:]} {hex(random.choice(range(0,100)))[2:]} {hex(random.choice(range(0,100)))[2:]} {hex(random.choice(range(0,100)))[2:]} {hex(random.choice(range(0,100)))[2:]} {hex(random.choice(range(0,100)))[2:]}"
            print(readline)
            time.sleep(0.1)
            #  Check if readline does not start with start or running
            if readline != 'start' and readline != 'running':
                #  Split with space
                readline = readline.split(' ')
                #  Check that readline is not corrupted
                if len(readline) == 7:
                    run = False
                    returnValue = {
                        "RGB": {
                            "R": int(readline[3], 16),
                            "G": int(readline[4], 16),
                            "B": int(readline[5], 16),
                        },
                        "Pos": {
                            "X": int(readline[0], 16),
                            "Y": int(readline[1], 16),
                            "Z": int(readline[2], 16),
                        }
                    }
                    return returnValue
       # Any issues lets ignore them
        except:
            pass


def debugMessages():
    pass


def newRGB():
    pass


class Pixel:
    def __init__(self, pos, colour, canvas, size):
        self.posy = pos["Y"]*size
        self.posx = pos["X"]*size
        self.size = size
        self.colour = colour
        self.canvas = canvas

        self.canvas.create_rectangle(self.posx, self.posy, self.posx + self.size,
                                     self.posy + self.size, fill=self.colour, outline=self.colour)


######## Tkinter objects ########
# Tkinter  Start button
class start_button:
    def __init__(self, frame, pos):
        self.text = "start scan"
        self.pos = pos
        self.colour = "green"
        self.Button = Button(frame, text=self.text,
                             bg=self.colour, command=lambda: self.start_press())
        self.Button.place(x=pos[0], y=pos[1])

    def start_press(self):
        # ser.write(1)
        pic_frame.delete('all')
        run_now()


######## End Tkinter objects ########


# Setup serial
# ser = serial.Serial('/dev/ttyACM0')

# Setup Tkinter
root = Tk()
root.minsize(750, 750)
root.title('Scanner')


# Get data from RGB and display
def run_now():
    RGBAndPos = read_RGBAndPos()
    red = RGBAndPos["RGB"]["R"]
    green = RGBAndPos["RGB"]["G"]
    blue = RGBAndPos["RGB"]["B"]

    col_string = '#%02x%02x%02x' % (red, green, blue)
    print(col_string)

    Pixel(pos=RGBAndPos["Pos"], colour=col_string, canvas=pic_frame, size=4)

    # root.after(1, run_now)




pic_frame = Canvas(root, width=500, height=500,
                   bg='light grey', borderwidth=5, relief=GROOVE)


pic_frame.place(x=0, y=0, anchor=NW)
listBox=Listbox(root,height=10)
listBox.place(x=550,y=100, anchor=NW)
start_button = start_button(root, (600, 0))

while (True):
    root.update_idletasks()
    root.update()

