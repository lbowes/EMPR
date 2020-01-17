# Remove annoying hello :(
import os
os.environ['PYGAME_HIDE_SUPPORT_PROMPT'] = "hide"

import pygame
import serial
from collections import namedtuple
from configparser import *
from  Pixel import Pixel

# Todo remove me
from time import sleep
import random




# Check we are the only ones running
if __name__ == "__main__":
    
    # -------- Load all our settings-------- #
    try:
        # Load the main config file
        config_parser = SafeConfigParser()
        config_parser.read('config.ini')
    except ParsingError:
        print("There is a problem with the config.ini file.")
        exit()
    # Try and load up all the config stuff
    try:
        Autoscale = config_parser.getboolean('settings', 'autoscale')
        _height = config_parser.getint('settings', 'height')
        _width = config_parser.getint('settings', 'width')
        _port = config_parser.get('settings', 'port')
        centerImage = config_parser.getboolean('settings','centerImage')
    except Exception:
        print("There is an issue with the config file please make sure you have all the settings required.")
        exit()
    # -------- Finished loading our settings -------- #
    
    # -------- Setup -------- #

    # Initialise pygame
    pygame.init()

    

    # Setup logo
    logo = pygame.image.load("logo.jpeg")
    pygame.display.set_icon(logo)
    pygame.display.set_caption("Nigerian Scanner")
    
    # Setup window
    Window={'height':_height,'width':_width}

    # If autoscale go to the largest mode
    if Autoscale:
        modes=pygame.display.list_modes()
        Window['width']=modes[0][0]
        Window['height']=modes[0][1]

    # Setup surface
    surface=pygame.display.set_mode((Window['width'],Window['height']))
    


    #image array
    imageArray=[]

    # TODO setup serial input

    # Running?
    Running=True

    # Used for calculation 
    maxPixelX=0
    maxPixelY=0
    # -------- End Setup -------- #
    while Running:
        # Clear the screen
        # surface.fill((0,0,0))

        # Todo remove me Emulate  serial input
        # x,y,z,r,g,b=input().split()
        x,y,z,r,g,b=random.randint(0,1919),random.randint(0,1079),1,random.randint(0,255),random.randint(0,255),random.randint(0,255)
        #Hack z is always 1 for this 2D scanner
        z = 1
        
        # Check if its a new pixel in which case append otherwise update
        newPixel=Pixel(x,y,z,r,g,b)
        if newPixel in imageArray:
            imageArray[imageArray.index(newPixel)].updateAndAverage(r,g,b)
        else:
            imageArray.append(newPixel)
            if maxPixelX<x:
                maxPixelX=x
            if maxPixelY<y:
                maxPixelY=y


        # Calculate the max size of all the pixels
        maxPixelSize=int(min(Window['height']/(maxPixelY+1),Window['width']/(maxPixelX+1)))
        if (maxPixelSize==0):
            raise Exception("You have run out of Pixels, now you need to consider subsampling or making your res higher")
        # If center image calculate offsets
        if centerImage:
            xOffset = int((Window['width']-((maxPixelX+1)*maxPixelSize))/2)
            yOffset = int((Window['height']-((maxPixelY+1)*maxPixelSize))/2)
        # Iterate through and draw all pixels
        # for pixel in imageArray:
        if not centerImage:
                # X , Y , W , H
            pygame.draw.rect(surface, newPixel.getRGB(), (newPixel.x*maxPixelSize,newPixel.y*maxPixelSize,maxPixelSize,maxPixelSize))
        else:
                # X + xOffset , Y + yOffset, W , H
            pygame.draw.rect(surface, pixel.getRGB(), ((newPixel.x*maxPixelSize)+xOffset,(newPixel.y*maxPixelSize)+yOffset,maxPixelSize,maxPixelSize))
        # Check if we are getting an abort
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                # Exit, pursued by a bear 
                Running=False
                # Todo serial cleanup
            # Todo when press s then gen image
        pygame.display.update()
        # sleep(0.01)