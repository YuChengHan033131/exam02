import matplotlib.pyplot as plt
import numpy as np
import serial
import struct #bytes and float convert

serdev = '/dev/ttyACM0'
s = serial.Serial(serdev)
x=[]
y=[]
z=[]
t=[]
dis=[]
line=s.readline()
while 1:
    x.append(line)
    line=s.readline()
    y.append(line)
    line=s.readline()
    z.append(line)
    line=s.readline()
    t.append(line)
    line=s.readline()
    dis.append(line)
    line=s.readline()
    if 'END' in line.decode():#decode because line is a bytes-like-object,need decode to string
        break
print('done')
tilt=[-1]*len(x)
for i in range(len(x)):
    x[i]=float(x[i].decode().strip())
    y[i]=float(y[i].decode().strip())
    z[i]=float(z[i].decode().strip())
    t[i]=float(t[i].decode().strip()) #strip : remove \r\n
    dis[i]=float(dis[i].decode().strip())
   
plt.subplot(211)
plt.plot(t,x,label='x',color='red')
plt.plot(t,y,label='y',color='green')
plt.plot(t,z,label='z',color='blue')
plt.xlim(0,10)
plt.ylim(-1.2,1.2)
plt.xlabel('Time')
plt.ylabel('Acc Vecotr')
plt.legend() #map example
plt.subplot(212)
plt.scatter(t,dis)
plt.xlim(0,10)
plt.ylim(0,1.0)
plt.xlabel('Time')
plt.ylabel('displacement event')
plt.show()