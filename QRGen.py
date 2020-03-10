
from tkinter import *


width = 60
height = 60


root = Tk()
root.minsize(900,900)
cv = Canvas(root, width = 900, height = 900)
cv.place (x = 0, y = 0)
target = input()
encode_list = []
for o in target:
    encode_list.append(bin(ord(o)-96))




code = encode_list
#[bin(ord('a')-96),bin(ord('b')-96),bin(ord('c')-96),bin(ord('d')-96)]

#print('0'*(8-len(str(bin(code[0]))[2:])) + str(bin(code[0]))[2:])

for i in range(len(code)+1):
    if i != len(code):
        line = (('0'*(5-len(str(code[i])[2:])) + str(code[i])[2:]) + '0' + ('0'*(5-len(str(code[i])[2:])) + str(code[i])[2:])[::-1])
    else:
        
        #line = '23000000000'
        line = '00000000000'

    print(line)
    for k in range(len(line)):
        if line[k] == '1':
            cv.create_rectangle(k*width, i*height, k*width + width, i*height + height, fill = '#000000', outline = '#000000')
            

        elif line[k] == '0':
            cv.create_rectangle(k*width, i*height, k*width + width, i*height + height, fill = '#ffffff', outline = '#ffffff')

        # elif line[k] == '2' :
        #     cv.create_rectangle(k*width, i*height, k*width + width, i*height + height, fill = 'pink', outline = 'pink')

        # elif line[k] == '3' :
        #     cv.create_rectangle(k*width, i*height, k*width + width, i*height + height, fill = 'yellow', outline = 'yellow')

        
        #Fm.place(x = k*width, y = i*height)
    

        
root.mainloop()