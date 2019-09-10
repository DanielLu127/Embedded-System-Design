from tkinter import *
from pymongo import MongoClient
from tkinter.ttk import Separator

def init_mongo():
    global client
    client = MongoClient('localhost', 27017)#defaults
    global db
    db = client['ECE4534_test']
    global collection
    collection = db['collection']

def getDirection(var):
    if var == 0:
        return "None"
    elif var == 1:
        return "left"
    elif var == 2:
        return "right"
    else:
        return "No change"

def updateX(x):
    return 'x : ' + str(x)

def updateY(y):
    return 'y : ' + str(y)

def updatePiDeg(piDeg):
    return 'piDeg : ' + str(piDeg)

def updatePiDir(piDir):
    append = ''
    if piDir == 0:
        append = 'Not detected'
    elif piDir == 1:
        append = 'left'
    elif piDir == 2:
        append = 'right'
    elif piDir == 3:
        append = 'No change needed'
    return "pi dir : " + append

def updateLabels(xvar, yvar , piDegvar, piDirvar, x, y , piDir, piDeg ):
    xvar.configure(text=updateX(x))
    yvar.configure(text=updateY(y))
    piDegvar.configure(text=updatePiDeg(piDeg))
    piDirvar.configure(text=updatePiDir(piDir))

def getColor(sig):
    if sig == 1:
        return "green"
    elif sig ==2:
        return "yellow"
    elif sig ==3:
        return "blue"
    elif sig ==4:
        return "red"

def updateRect(xvar, yvar, piDegvar, piDirvar):
    pixy = collection.find_one({"name" : "pixy3"})
    if pixy:
        piDir = pixy['piDir'] # keeps track of direction 
        w.delete('all')
        x = pixy['x'] # extracts the x
        y = pixy['y'] # extracts the y
        xlen = pixy['xlen'] # extracts the width
        ylen = pixy['ylen'] # extracts the height
        sig = pixy['sig']
        color = getColor(sig)
        w.create_rectangle(x-int(xlen/2), y-int(ylen/2), x+int(xlen/2) , y+int(ylen/2), fill=color, outline='black')
        updateLabels(xvar, yvar, piDegvar,piDirvar, x, y , piDir, pixy['piDegree'])
        master.after(5, updateRect, xvar, yvar, piDegvar, piDirvar)
		
def updateRect2(xvar, yvar, piDegvar, piDirvar):
    pixy = collection.find_one({"name" : "pixy4"})
    if pixy:
        piDir = pixy['piDir'] # keeps track of direction 
        w2.delete('all')
        x = pixy['x'] # extracts the x
        y = pixy['y'] # extracts the y
        xlen = pixy['xlen'] # extracts the width
        ylen = pixy['ylen'] # extracts the height
        sig = pixy['sig']
        color = getColor(sig)
        w2.create_rectangle(x-int(xlen/2), y-int(ylen/2), x+int(xlen/2) , y+int(ylen/2), fill=color, outline='black')
        updateLabels(xvar, yvar, piDegvar,piDirvar, x, y , piDir, pixy['piDegree'])
        master.after(5, updateRect2, xvar, yvar, piDegvar, piDirvar)
		
init_mongo()

if __name__ == '__main__':
    master = Tk()
    left = Frame(master, width=400, height=400)
    left.pack_propagate(False)
    Title = Label(left ,text='Pixy 3 GUI' , anchor='center')
    xvar = Label(left ,text="x : 0" , anchor='w')
    yvar = Label(left,text="y : 0" , anchor='w')
    piDegvar = Label(left,text="piDeg : 0", anchor='w')
    piDirvar = Label(left, text="piDir : none", anchor='w')
    Title.pack()
    xvar.pack()
    yvar.pack()
    piDegvar.pack()
    piDirvar.pack()
    canvas_width = 315
    canvas_height = 208
    w = Canvas(left, width=canvas_width,height=canvas_height)
    w.pack(anchor=SW)
    updateRect(xvar, yvar, piDegvar, piDirvar)
    left.grid(column=0, row=0, pady=5, padx=10, sticky='n')
    sep = Separator(master, orient="vertical")
    sep.grid(column=1, row=0, sticky="ns")
	# right hand side should be pixy4
    right = Frame(master, width=400, height=400)
    right.pack_propagate(True)
    Title2 = Label(right,text='Pixy 4 GUI', anchor='center')
    xvar2 = Label(right,text="x : 0" , anchor='e')
    yvar2 = Label(right,text="y : 0" , anchor='e')
    piDegvar2 = Label(right,text="piDeg : 0", anchor='e')
    piDirvar2 = Label(right, text="piDir : none", anchor='e')
    Title2.pack()
    xvar2.pack()
    yvar2.pack()
    piDegvar2.pack()
    piDirvar2.pack()
    w2 = Canvas(right, width=canvas_width,height=canvas_height)
    w2.pack(anchor=SE)
    updateRect2(xvar2, yvar2, piDegvar2, piDirvar2)
    right.grid(column=2, row=0, pady=5, padx=10, sticky='n')	
    master.mainloop()
