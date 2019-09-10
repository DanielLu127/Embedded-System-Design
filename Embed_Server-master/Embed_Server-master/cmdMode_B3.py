import time
import pymongo
from pymongo import MongoClient

#Default host and port
client = MongoClient('localhost', 27017)
#Get database "ECE4534_test" (or create it)
db = client['ECE4534_test']
collection = db['collection']

def goStraight():
    print ("Send action command: Go Straight")
    collection.update_one({"name":"motor3"}, {"$set": 
        {"mtAction":2,"mtDegree":0}})
    while True:
        motor = collection.find_one({"name": "motor3"})
        if motor['mtAction'] == 2:
           time.sleep(0.1)
        elif motor['mtAction'] == 11:
            print("Verified Status")
            break;
        else:
            print(motor['mtAction'])
            print("Error to put the motor moving")
            break
    input("Press Enter to continue...")
    collection.update_one({"name":"motor3"}, {"$set": {"mtAction":4,"mtDegree":0}})
    print ("Finish action and stop motor")

def goBack():
    print ("Send action command: Go Back")
    collection.update_one({"name":"motor3"}, {"$set": {"mtAction":3,"mtDegree":0}})
    input("Press Enter to continue...")
    collection.update_one({"name":"motor3"}, {"$set": {"mtAction":4,"mtDegree":0}})
    print ("Finish action and stop motor")

def turnRight():
    print ("Send action command: Turn Right")
    collection.update_one({"name":"motor3"}, {"$set": {"mtAction":5,"mtDegree":0}})
    while True:
        motor = collection.find_one({"name": "motor3"})
        if motor['mtAction'] == 1:
            break
        else:
            time.sleep(0.1)

def turnRightSpec(num):
    print ("Send action command: Turn Right for %d" % num)
    collection.update_one({"name":"motor3"}, {"$set": {"mtAction":8,"mtDegree":num}})
    while True:
        motor = collection.find_one({"name": "motor3"})
        if motor['mtAction'] == 1:
            break
        else:
            time.sleep(0.1)

def turnLeft():
    print ("Send action command: Turn Left")
    collection.update_one({"name":"motor3"}, {"$set": {"mtAction":6,"mtDegree":0}})
    while True:
        motor = collection.find_one({"name": "motor3"})
        if motor['mtAction'] == 1:
            break
        else:
            time.sleep(0.1)

def turnLeftSpec(num):
    print ("Send action command: Turn Left for %d" % num)
    collection.update_one({"name":"motor3"}, {"$set": {"mtAction":7,"mtDegree":num}})
    while True:
        motor = collection.find_one({"name": "motor3"})
        if motor['mtAction'] == 1:
            break
        else:
            time.sleep(0.1)

def testFuc():
    # Init data in the database
    print ("Initializing database...")
    motor = collection.find_one({"name": "motor3"})
    if motor:
        collection.update_one({"name":"motor3"}, {"$set": {"mtAction":0,"mtDegree":0}})
    else:
        collection.insert_one({"name":"motor3","mtAction":0,"mtDegree":0})
    
    # Wait until correct connection set up
    print ("Connecting to Board...")
    while True:
        motor = collection.find_one({"name": "motor3"})
        if motor['mtAction'] == 1:
            break
        else:
            time.sleep(0.5)
    print ("Connection Successful!")

    print("Welcome to rover control program!\nHere are the avaliable commands:")
    print("\t1) f: Go straight and press enter to stop.\n\t2) b: Go back and press enter to stop.\n\t3) r: Turn right with specific degrees.\n\t4) r90: Turn right with 90 degrees.\n\t5) l: Turn left with specific degrees.\n\t6) l90: Turn left with 90 degrees.\n\t7) s: Stop the rover.\n\t8) stop: Stop the program.")
    while True:
        inStr = input("Enter command:")
        if inStr == "f":
            goStraight()
        elif inStr == "b":
            goBack()
        elif inStr == "r":
            tmp = input("Enter the degrees to be turn:")
            try:
                val = int(tmp)
                turnRightSpec(val)
            except ValueError:
                print("Degree has to be a number")
        elif inStr == "r90":
            turnRight()
        elif inStr == "l":
            tmp = input("Enter the degrees to be turn:")
            try:
                val = int(tmp)
                turnLeftSpec(val)
            except ValueError:
                print("Degree has to be a number")
        elif inStr == "l90":
            turnLeft()
        elif inStr == "s":
            collection.update_one({"name":"motor3"}, {"$set": {"mtAction":4,"mtDegree":0}})
        elif inStr == "stop":
            print("Program stops")
            break
        else:
            print("Invalid command!")

def printData():
    testFuc()

if __name__ == '__main__':
    printData()

