
#How to use range function
#range(number)
#range(start value,end value)
#range(start value,end value,step value)
#


from tkinter import *

w = Canvas(Tk(), width=900,height=400)
w.pack()

for i in range(300,600,1):#start value is 300 end value is 600 step value is 1
    x = i
    w.create_line(x,0,x,400,fill="#00FF00")

mainloop()              