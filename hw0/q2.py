from PIL import Image
import getopt
import sys
import numpy as np

arg=sys.argv[1]

im=Image.open(arg)
A=np.array(im);
A=A[::-1,::-1]

con=Image.fromarray(A)
con.save("ans2.png")
