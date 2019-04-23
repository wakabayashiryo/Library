from tkinter import *
from tkinter import ttk 

win = Tk() 
win.title(u"Software Title")
win.geometry("400x300")
Button = Button(text=u'test')
check = Checkbutton(text='hello')
home = ttk.Radiobutton(text='Home',value='home')
Office = ttk.Radiobutton(text='Office',value='office')
cell = ttk.Radiobutton(text='Cell',value='cell')
home.pack()
Office.pack()
cell.pack()
# check.pack()
# Button.pack()
win.mainloop()