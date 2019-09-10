from tkinter import *
import tkinter as tk
import pymongo
from pymongo import MongoClient

#Default host and port
client = MongoClient('localhost', 27017)
#Get database "ECE4534_test" (or create it)
db = client['ECE4534_test']
collection = db['collection']

root = Tk()

lab3 = Label(root)
lab3.pack()

lab4 = Label(root)
lab4.pack()

def clock():
    data3 = collection.find_one({"name":"sonar3"})
    sonarDis3 = data3["sonarDis"]
    distance3 = "Board3 Sonar Distance: " + str(sonarDis3) + " inches"
    lab3.config(text=distance3)
    
    data4 = collection.find_one({"name":"sonar4"})
    sonarDis4 = data4["sonarDis"]
    distance4 = "Board4 Sonar Distance: " + str(sonarDis4) + " inches"
    lab4.config(text=distance4)
    root.after(100, clock) # run itself again after 100 ms

root.title('Distance Plot')

root.geometry("300x300")
lab3.place(x=50, y=100)

lab4.place(x=50, y=160)

clock()
root.mainloop()
