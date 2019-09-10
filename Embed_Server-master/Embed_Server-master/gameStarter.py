import time
import pymongo
from pymongo import MongoClient

#Default host and port
client = MongoClient('localhost', 27017)
#Get database "ECE4534_test" (or create it)
db = client['ECE4534_test']
collection = db['collection']

def testFuc():
    # Init data in the database
    arm = collection.find_one({"name": "arm"})
    if arm:
        collection.update_one({"name":"arm"}, {"$set": {"armAction":0}})
    else:
        collection.insert_one({"name":"arm","armAction":0})
        
    game = collection.find_one({"name": "game"})
    if game:
        collection.update_one({"name":"game"}, {"$set": {"board":0}})
    else:
        collection.insert_one({"name":"game","board":0})
    
    motor = collection.find_one({"name": "motor"})
    if motor:
	    collection.update_one({"name":"motor"}, {"$set": {"mtAction":0,"mtDegree":0}})
    else:
	    collection.insert_one({"name":"motor","mtAction":0,"mtDegree":0})
      
    pixy = collection.find_one({"name": "pixy"})
    if pixy:
	    collection.update_one({"name":"pixy"}, {"$set": {"piDir":0,"piDegree":0, "x":0, "y":0, "sig":0, "xlen":0, "ylen":0}})
    else:
	    collection.insert_one({"name":"pixy","piDir":0,"piDegree":0, "x":0, "y":0, "sig":0, "xlen":0, "ylen":0})
    
    sonar = collection.find_one({"name": "sonar"})
    if sonar:
	    collection.update_one({"name":"sonar"}, {"$set": {"sonarDir":0,"sonarDis":0}})
    else:
	    collection.insert_one({"name":"sonar","sonarDir":0,"sonarDis":0})
    
    motor3 = collection.find_one({"name": "motor3"})
    if motor3:
	    collection.update_one({"name":"motor3"}, {"$set": {"mtAction":0,"mtDegree":0}})
    else:
	    collection.insert_one({"name":"motor3","mtAction":0,"mtDegree":0})

    motor4 = collection.find_one({"name": "motor4"})
    if motor4:
        collection.update_one({"name":"motor4"}, {"$set": {"mtAction":0,"mtDegree":0}})
    else:
        collection.insert_one({"name":"motor4","mtAction":0,"mtDegree":0})
	
    pixy2 = collection.find_one({"name": "pixy2"})
    if pixy2:
        collection.update_one({"name":"pixy2"}, {"$set": {"piStart":0}})
    else:
        collection.insert_one({"name":"pixy2","piStart":0})
	
    pixy3 = collection.find_one({"name": "pixy3"})
    if pixy3:
        collection.update_one({"name":"pixy3"}, {"$set": {"piDir":0, "piDegree":0, "x":0, "y":0, "sig":0, "xlen":0, "ylen":0}})
    else:
        collection.insert_one({"name":"pixy3","piDir":0, "piDegree":0, "x":0, "y":0, "sig":0, "xlen":0, "ylen":0})
	
    pixy4 = collection.find_one({"name": "pixy4"})
    if pixy4:
        collection.update_one({"name":"pixy4"}, {"$set": {"piDir":0, "piDegree":0, "x":0, "y":0, "sig":0, "xlen":0, "ylen":0}})
    else:
        collection.insert_one({"name":"pixy4","piDir":0, "piDegree":0, "x":0, "y":0, "sig":0, "xlen":0, "ylen":0})
	
    sonar3 = collection.find_one({"name": "sonar3"})
    if sonar3:
        collection.update_one({"name":"sonar3"}, {"$set": {"sonarDir":0,"sonarDis":0}})
    else:
        collection.insert_one({"name":"sonar3","sonarDir":0,"sonarDis":0})
	
    sonar4 = collection.find_one({"name": "sonar4"})
    if sonar4:
        collection.update_one({"name":"sonar4"}, {"$set": {"sonarDir":0,"sonarDis":0}})
    else:
        collection.insert_one({"name":"sonar4","sonarDir":0,"sonarDis":0})
    
    # Wait until correct connection set up
    print ("Connecting to Board 1...")
    while True:
        arm = collection.find_one({"name": "arm"})
        if arm['armAction'] == 1:
            break
        else:
            time.sleep(0.1)
        
    print ("Connecting to Board 2...")
    while True:
        game = collection.find_one({"name": "game"})
        if game['board'] == 1:
            break
        else:
            time.sleep(0.1)
    
    print ("Connecting to Board 3...")
    while True:
        motor3 = collection.find_one({"name": "motor3"})
        if motor3['mtAction'] == 1:
            break
        else:
            time.sleep(0.1)

    print ("Connecting to Board 4...")
    while True:
        motor4 = collection.find_one({"name": "motor4"})
        if motor4['mtAction'] == 1:
            break
        else:
            time.sleep(0.1)
    print ("Connection Successful!")
	
    input("Press Enter to continue...")
    
    print ("Running the game for Rover 1...")
    collection.update_one({"name":"game"}, {"$set": {"board":5}})
    while True:
        game = collection.find_one({"name": "game"})
        if game['board'] == 1:
            break
        else:
            time.sleep(0.1)
	
    #input("Press enter to continue...")
    
    print ("Running the game for Rover 2...")
    collection.update_one({"name":"game"}, {"$set": {"board":6}})
    while True:
        game = collection.find_one({"name": "game"})
        if game['board'] == 1:
            break
        else:
            time.sleep(0.1)
	    
    print ("Game Finish!")

def printData():
	testFuc()

if __name__ == '__main__':
	printData()
