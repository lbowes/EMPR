import serial
serialLine = serial.Serial("/dev/ttyACM0",baudrate=460800)
log=open("log.txt","a")
while (1):
    # print()
    log.write(serialLine.readline().decode('utf-8'))
    log.flush()