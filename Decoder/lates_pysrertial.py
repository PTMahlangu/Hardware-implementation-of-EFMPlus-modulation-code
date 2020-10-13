from textwrap import wrap
import serial
import numpy as np
import random 
import time
import string

#ser = serial.Serial(
#    port='COM6',
#    baudrate=9600,
#    stopbits=serial.STOPBITS_ONE,
#    bytesize=serial.EIGHTBITS )
#
samples =15
#ser.isOpen
#inputData1 = []
#
#for x in range(samples):
#   inputData1.append(random.randint(0,255))
#   
#
#for i in range(len(inputData1)):
#    X = '{:03d}'.format(inputData1[i])
#    data = str(X).encode('utf-8')
#    ser.write(data) 
#    time.sleep(1)
#    
#    
#ser.close()
#
#print("Data sent")
#[print(x) for x in inputData1]
################################################
ser = serial.Serial(
    port='COM5',
    baudrate=9600,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS )

ser.isOpen

seq = [0]*(5*(samples-1))
count = 1
joined=[]

while (count <= 5*(samples-1)):
    for c in ser.read():
        seq[count-1]=(chr(c)) #convert from ANSII
       # joined_seq = ''.join(str(v) for v in seq)       
        count = count + 1
        
j=1
v=1
p=0 
joined=[]
A=[0]*len(seq)      
for i in range (len(seq)):
    if(j!=5*v-p):
        A[i] =seq[i]
        joined.append(A[i])
        j=j+1
    else:
        v=v+1
        p=p+1 
#joined="".join(map(str,seq))
joined = ''.join(str(m) for m in joined)
Wrap_Data = wrap(joined, 4)
Out_data = [ int(x,16) for x in Wrap_Data]
     
ser.close()
print("Data Received:")
[print(x) for x in Out_data]
#################

