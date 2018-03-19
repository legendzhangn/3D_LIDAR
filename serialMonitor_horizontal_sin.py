import serial
import time
import os
import sys
import math

ser = serial.Serial('COM6', 115200);
time.sleep(3)
#ser.write('s'.encode());

#while True:
#    print ser.readline()
	
file0 = open("results.txt", "w");
scan = 1;	
angleOld = -1;
#angleOld = 1000;
dist = []; horAngle = []; verAngle = [];
x = []; y = []; z = [];
while scan:
  myline =  ser.readline().decode("utf-8");
  print(myline.rstrip('\n'));
  data = myline.rstrip('\n').split(' ');
  #print(data[0])
  #print(data[1])
  #print(data[2])
  if (len(myline.rstrip('\n')) > 3):
    #file0.write(myline.rstrip('\n'));
    file0.write(data[0]+' '+data[1]+' '+data[2]+'\n');
  if (len(myline.rstrip('\n')) <= 3):
    scan = 0;
    break;

file0.close();

