from PIL import Image
import getopt
import sys
import numpy as np

col=sys.argv[1]
arg=sys.argv[2]


file=open(arg,'r')

data=[]

for line in file:
    data.append(line.strip().split(' '))
file.close()

A=np.array(data)
A=A[:,col]

B=[]
for k in range(A.shape[0]):
    B.append(float(A[k]))
B=sorted(B)


con=''
for k in range(A.shape[0]):
    con=con+str(B[k])+','


con=con[0:len(con)-1]

f=open('ans1.txt','w')
f.write(con)

