#/*	UFUK GÜRBÜZ - 150113058 */
import sys
import re
import os
import psutil # if this makes an error, you need to install the psutil package on your system
from Tkinter import *

root =  Tk()
S = Scrollbar(root)
T = Text(root, height=35, width=80)
S.pack(side=RIGHT, fill=Y)
T.pack(side=LEFT, fill=Y)
S.config(command=T.yview)
T.config(yscrollcommand=S.set)


# make sure the user gave us a file to read
if len(sys.argv) != 2:
  print "need one argument! (file to read from)"
  sys.exit(-1)
filename = sys.argv[1]

# read input file
#print "reading from file "+filename
f = open(filename,'r')

metin = ""


for line in f:
        
  metin = metin + line



T.insert(END, metin)

mainloop()
