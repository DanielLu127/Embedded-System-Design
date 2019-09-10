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
        collection.update_one({"name":"arm"}, {"$set": {"armAction":1}})
    else:
        collection.insert_one({"name":"arm","armAction":1})
        
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
	    collection.update_one({"name":"sonar"}, {"$set": {"sonarDir":0,"sonarDistance":0}})
    else:
	    collection.insert_one({"name":"sonar","sonarDir":0,"sonarDistance":0})
    
    motor3 = collection.find_one({"name": "motor3"})
    if motor3:
	    collection.update_one({"name":"motor3"}, {"$set": {"mtAction":1,"mtDegree":0}})
    else:
	    collection.insert_one({"name":"motor3","mtAction":1,"mtDegree":0})

    motor4 = collection.find_one({"name": "motor4"})
    if motor4:
        collection.update_one({"name":"motor4"}, {"$set": {"mtAction":1,"mtDegree":0}})
    else:
        collection.insert_one({"name":"motor4","mtAction":1,"mtDegree":0})
	
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
        collection.update_one({"name":"sonar3"}, {"$set": {"sonarDir":0,"sonarDistance":0}})
    else:
        collection.insert_one({"name":"sonar3","sonarDir":0,"sonarDistance":0})
	
    sonar4 = collection.find_one({"name": "sonar4"})
    if sonar4:
        collection.update_one({"name":"sonar4"}, {"$set": {"sonarDir":0,"sonarDistance":0}})
    else:
        collection.insert_one({"name":"sonar4","sonarDir":0,"sonarDistance":0})
    
    # Wait until correct connection set up
    print ("Connecting to Board...")
    while True:
        game = collection.find_one({"name": "game"})
        if game['board'] == 1:
            break
        else:
            time.sleep(0.1)
    print ("Connection Successful!")
    
    input("Press Enter to continue...")
    print("Start game...")
    collection.update_one({"name":"game"}, {"$set": {"board":5}})
    
    # Test Case 1
    print("Rover 3 should gets go straight command")
    while True:
        motor3 = collection.find_one({"name": "motor3"})
        if motor3['mtAction'] == 2:
            break
        else:
            time.sleep(0.1)
    collection.update_one({"name":"motor3"}, {"$set": {"mtAction":11,"mtDegree":0}})
    print("Successful! Test case 1")
    
    #input("Press Enter to continue...")
    
    # Test Case 2
    print("Adjusting 30 degrees left interrupt comes from pixy3")
    collection.update_one({"name":"pixy3"}, {"$set": {"piDir":1, "piDegree":30}})
    print("Rover 3 should gets turning left 30 degree command")
    while True:
        motor3 = collection.find_one({"name": "motor3"})
        if motor3['mtAction'] == 7:
            break
        else:
            time.sleep(0.1)
    if motor3['mtDegree'] != 30:return
	
    time.sleep(2)
    collection.update_one({"name":"pixy3"}, {"$set": {"piDir":0, "piDegree":0}})
    collection.update_one({"name":"motor3"}, {"$set": {"mtAction":1,"mtDegree":0}})
    
    print("Successfully recieve motor command. Then we should get going straight command again")
    while True:
        motor3 = collection.find_one({"name": "motor3"})
        if motor3['mtAction'] == 2:
            break
        else:
            time.sleep(0.1)
    collection.update_one({"name":"motor3"}, {"$set": {"mtAction":11,"mtDegree":0}})
    print("Successful! Test case 2")
    
    #input("Press Enter to continue...")
    
    # Test Case 3
    print("Adjusting 30 degrees right interrupt comes from pixy3")
    collection.update_one({"name":"pixy3"}, {"$set": {"piDir":2, "piDegree":30}})
    print("Rover 3 should gets turning right 30 degree command")
    while True:
        motor3 = collection.find_one({"name": "motor3"})
        if motor3['mtAction'] == 8:
            break
        else:
            time.sleep(0.1)
    if motor3['mtDegree'] != 30:return
	
    time.sleep(2)
    collection.update_one({"name":"pixy3"}, {"$set": {"piDir":0, "piDegree":0}})
    collection.update_one({"name":"motor3"}, {"$set": {"mtAction":1,"mtDegree":0}})
    
    print("Successfully recieve motor command. Then we should get going straight command again")
    while True:
        motor3 = collection.find_one({"name": "motor3"})
        if motor3['mtAction'] == 2:
            break
        else:
            time.sleep(0.1)
    collection.update_one({"name":"motor3"}, {"$set": {"mtAction":11,"mtDegree":0}})
    print("Successful! Test case 3")
    
    #input("Press Enter to continue...")
    
    # Test Case 4
    print("Sonar3 gives the interrupt for the first turning")
    collection.update_one({"name":"sonar3"}, {"$set": {"sonarDir":1}})
    while True:
        motor3 = collection.find_one({"name": "motor3"})
        if motor3['mtAction'] == 6:
            break
        else:
            time.sleep(0.1)
	
    time.sleep(2)
    collection.update_one({"name":"sonar3"}, {"$set": {"sonarDir":0}})
    collection.update_one({"name":"motor3"}, {"$set": {"mtAction":1,"mtDegree":0}})
    
    print("Successfully recieve motor command. Then we should get going straight command again")
    while True:
        motor3 = collection.find_one({"name": "motor3"})
        if motor3['mtAction'] == 2:
            break
        else:
            time.sleep(0.1)
    collection.update_one({"name":"motor3"}, {"$set": {"mtAction":11,"mtDegree":0}})
    print("Successful! Test case 4")
    
    #input("Press Enter to continue...")
    
    # Test Case 5
    print("Sonar3 gives the interrupt for the second turning")
    collection.update_one({"name":"sonar3"}, {"$set": {"sonarDir":1}})
    while True:
        motor3 = collection.find_one({"name": "motor3"})
        if motor3['mtAction'] == 6:
            break
        else:
            time.sleep(0.1)
	
    time.sleep(2)
    collection.update_one({"name":"sonar3"}, {"$set": {"sonarDir":0}})
    collection.update_one({"name":"motor3"}, {"$set": {"mtAction":1,"mtDegree":0}})
    
    print("Successfully recieve motor command. Then we should get going straight command again")
    while True:
        motor3 = collection.find_one({"name": "motor3"})
        if motor3['mtAction'] == 2:
            break
        else:
            time.sleep(0.1)
    collection.update_one({"name":"motor3"}, {"$set": {"mtAction":11,"mtDegree":0}})
    print("Successful! Test case 5")
    
    #input("Press Enter to continue...")
    
    # Test Case 6
    print("Adjusting 30 degrees left interrupt comes from pixy3")
    collection.update_one({"name":"pixy3"}, {"$set": {"piDir":1, "piDegree":30}})
    print("Rover 3 should gets turning left 30 degree command")
    while True:
        motor3 = collection.find_one({"name": "motor3"})
        if motor3['mtAction'] == 7:
            break
        else:
            time.sleep(0.1)
    if motor3['mtDegree'] != 30:return
	
    time.sleep(2)
    collection.update_one({"name":"pixy3"}, {"$set": {"piDir":0, "piDegree":0}})
    collection.update_one({"name":"motor3"}, {"$set": {"mtAction":1,"mtDegree":0}})
    
    print("Successfully recieve motor command. Then we should get going straight command again")
    while True:
        motor3 = collection.find_one({"name": "motor3"})
        if motor3['mtAction'] == 2:
            break
        else:
            time.sleep(0.1)
    collection.update_one({"name":"motor3"}, {"$set": {"mtAction":11,"mtDegree":0}})
    print("Successful! Test case 6")
    
    #input("Press Enter to continue...")
    
    # Test Case 7
    print("Adjusting 30 degrees right interrupt comes from pixy3")
    collection.update_one({"name":"pixy3"}, {"$set": {"piDir":2, "piDegree":30}})
    print("Rover 3 should gets turning right 30 degree command")
    while True:
        motor3 = collection.find_one({"name": "motor3"})
        if motor3['mtAction'] == 8:
            break
        else:
            time.sleep(0.1)
    if motor3['mtDegree'] != 30:return
	
    time.sleep(2)
    collection.update_one({"name":"pixy3"}, {"$set": {"piDir":0, "piDegree":0}})
    collection.update_one({"name":"motor3"}, {"$set": {"mtAction":1,"mtDegree":0}})
    
    print("Successfully recieve motor command. Then we should get going straight command again")
    while True:
        motor3 = collection.find_one({"name": "motor3"})
        if motor3['mtAction'] == 2:
            break
        else:
            time.sleep(0.1)
    collection.update_one({"name":"motor3"}, {"$set": {"mtAction":11,"mtDegree":0}})
    print("Successful! Test case 7")
    
    # Test Case 8
    print("Arm pixy gives interrupt and rover 3 should stop and arm works")
    collection.update_one({"name":"pixy2"}, {"$set": {"piStart":1}})
    print("Rover 3 should gets turning right 30 degree command")
    while True:
        motor3 = collection.find_one({"name": "motor3"})
        arm = collection.find_one({"name": "arm"})
        if motor3['mtAction'] == 4 and  arm['armAction'] == 2:
            break
        else:
            time.sleep(0.1)
    collection.update_one({"name":"motor3"}, {"$set": {"mtAction":1,"mtDegree":0}})
    time.sleep(2)
    collection.update_one({"name":"arm"}, {"$set": {"armAction":1}})
    
    print("After arm action, motor should move")
    while True:
        motor3 = collection.find_one({"name": "motor3"})
        if motor3['mtAction'] == 2:
            break
        else:
            time.sleep(0.1)
    collection.update_one({"name":"motor3"}, {"$set": {"mtAction":11,"mtDegree":0}})
    print("Successful! Test case 8")
    
    #input("Press Enter to continue...")
    
    # Test Case 9
    print("Sonar3 gives the interrupt for the third turning")
    collection.update_one({"name":"sonar3"}, {"$set": {"sonarDir":1}})
    while True:
        motor3 = collection.find_one({"name": "motor3"})
        if motor3['mtAction'] == 6:
            break
        else:
            time.sleep(0.1)
	
    time.sleep(2)
    collection.update_one({"name":"sonar3"}, {"$set": {"sonarDir":0}})
    collection.update_one({"name":"motor3"}, {"$set": {"mtAction":1,"mtDegree":0}})
    
    print("Successfully recieve motor command. Then we should get going straight command again")
    while True:
        motor3 = collection.find_one({"name": "motor3"})
        if motor3['mtAction'] == 2:
            break
        else:
            time.sleep(0.1)
    collection.update_one({"name":"motor3"}, {"$set": {"mtAction":11,"mtDegree":0}})
    print("Successful! Test case 9")
    
    #input("Press Enter to continue...")
    
    # Test Case 10
    print("Sonar3 gives the interrupt for the forth turning")
    collection.update_one({"name":"sonar3"}, {"$set": {"sonarDir":1}})
    while True:
        motor3 = collection.find_one({"name": "motor3"})
        if motor3['mtAction'] == 6:
            break
        else:
            time.sleep(0.1)
	
    time.sleep(2)
    collection.update_one({"name":"sonar3"}, {"$set": {"sonarDir":0}})
    collection.update_one({"name":"motor3"}, {"$set": {"mtAction":1,"mtDegree":0}})
    
    print("Successfully recieve motor command. Then we should get going straight command again")
    while True:
        motor3 = collection.find_one({"name": "motor3"})
        if motor3['mtAction'] == 2:
            break
        else:
            time.sleep(0.1)
    collection.update_one({"name":"motor3"}, {"$set": {"mtAction":11,"mtDegree":0}})
    print("Successful! Test case 10")
    collection.update_one({"name":"pixy2"}, {"$set": {"piStart":0}})
    
    #input("Press Enter to continue...")
    
    # Test Case 11
    print("Sonar3 gives the interrupt for the fifth turning")
    collection.update_one({"name":"sonar3"}, {"$set": {"sonarDir":1}})
    while True:
        motor3 = collection.find_one({"name": "motor3"})
        if motor3['mtAction'] == 4:
            break
        else:
            time.sleep(0.1)
	
    print("Successfully rover 3 stop")
    collection.update_one({"name":"motor3"}, {"$set": {"mtAction":1,"mtDegree":0}})
    collection.update_one({"name":"game"}, {"$set": {"board":6}})

    print("Successfully rover 4 should start")
    while True:
        motor4 = collection.find_one({"name": "motor4"})
        if motor4['mtAction'] == 2:
            break
        else:
            time.sleep(0.1)
    collection.update_one({"name":"motor4"}, {"$set": {"mtAction":11,"mtDegree":0}})
    
    time.sleep(2)
    collection.update_one({"name":"sonar3"}, {"$set": {"sonarDir":0}})
    print("Successful! Test case 11")
    
    #input("Press Enter to continue...")
    
    # Test Case 1
    print("Adjusting 30 degrees left interrupt comes from pixy4")
    collection.update_one({"name":"pixy4"}, {"$set": {"piDir":1, "piDegree":30}})
    print("Rover 4 should gets turning left 30 degree command")
    while True:
        motor4 = collection.find_one({"name": "motor4"})
        if motor4['mtAction'] == 7:
            break
        else:
            time.sleep(0.1)
    if motor4['mtDegree'] != 30:return
	
    time.sleep(2)
    collection.update_one({"name":"pixy4"}, {"$set": {"piDir":0, "piDegree":0}})
    collection.update_one({"name":"motor4"}, {"$set": {"mtAction":1,"mtDegree":0}})
    
    print("Successfully recieve motor command. Then we should get going straight command again")
    while True:
        motor4 = collection.find_one({"name": "motor4"})
        if motor4['mtAction'] == 2:
            break
        else:
            time.sleep(0.1)
    collection.update_one({"name":"motor4"}, {"$set": {"mtAction":11,"mtDegree":0}})
    print("Successful! Test case 1")
    
    
    # Test Case 2
    print("Adjusting 30 degrees right interrupt comes from pixy4")
    collection.update_one({"name":"pixy4"}, {"$set": {"piDir":2, "piDegree":30}})
    print("Rover 4 should gets turning right 30 degree command")
    while True:
        motor4 = collection.find_one({"name": "motor4"})
        if motor4['mtAction'] == 8:
            break
        else:
            time.sleep(0.1)
    if motor4['mtDegree'] != 30:return
	
    time.sleep(2)
    collection.update_one({"name":"pixy4"}, {"$set": {"piDir":0, "piDegree":0}})
    collection.update_one({"name":"motor4"}, {"$set": {"mtAction":1,"mtDegree":0}})
    
    print("Successfully recieve motor command. Then we should get going straight command again")
    while True:
        motor4 = collection.find_one({"name": "motor4"})
        if motor4['mtAction'] == 2:
            break
        else:
            time.sleep(0.1)
    collection.update_one({"name":"motor4"}, {"$set": {"mtAction":11,"mtDegree":0}})
    print("Successful! Test case 2")
    
    
    # Test Case 3
    print("Sonar4 gives the interrupt for the first turning")
    collection.update_one({"name":"sonar4"}, {"$set": {"sonarDir":1}})
    while True:
        motor4 = collection.find_one({"name": "motor4"})
        if motor4['mtAction'] == 6:
            break
        else:
            time.sleep(0.1)
	
    time.sleep(2)
    collection.update_one({"name":"sonar4"}, {"$set": {"sonarDir":0}})
    collection.update_one({"name":"motor4"}, {"$set": {"mtAction":1,"mtDegree":0}})
    
    print("Successfully recieve motor command. Then we should get going straight command again")
    while True:
        motor4 = collection.find_one({"name": "motor4"})
        if motor4['mtAction'] == 2:
            break
        else:
            time.sleep(0.1)
    collection.update_one({"name":"motor4"}, {"$set": {"mtAction":11,"mtDegree":0}})
    print("Successful! Test case 3")
    
    
    # Test Case 4
    print("Sonar4 gives the interrupt for the second turning")
    collection.update_one({"name":"sonar4"}, {"$set": {"sonarDir":1}})
    while True:
        motor4 = collection.find_one({"name": "motor4"})
        if motor4['mtAction'] == 6:
            break
        else:
            time.sleep(0.1)
	
    time.sleep(2)
    collection.update_one({"name":"sonar4"}, {"$set": {"sonarDir":0}})
    collection.update_one({"name":"motor4"}, {"$set": {"mtAction":1,"mtDegree":0}})
    
    print("Successfully recieve motor command. Then we should get going straight command again")
    while True:
        motor4 = collection.find_one({"name": "motor4"})
        if motor4['mtAction'] == 2:
            break
        else:
            time.sleep(0.1)
    collection.update_one({"name":"motor4"}, {"$set": {"mtAction":11,"mtDegree":0}})
    print("Successful! Test case 4")
    
    
    # Test Case 5
    print("Adjusting 30 degrees left interrupt comes from pixy4")
    collection.update_one({"name":"pixy4"}, {"$set": {"piDir":1, "piDegree":30}})
    print("Rover 4 should gets turning left 30 degree command")
    while True:
        motor4 = collection.find_one({"name": "motor4"})
        if motor4['mtAction'] == 7:
            break
        else:
            time.sleep(0.1)
    if motor4['mtDegree'] != 30:return
	
    time.sleep(2)
    collection.update_one({"name":"pixy4"}, {"$set": {"piDir":0, "piDegree":0}})
    collection.update_one({"name":"motor4"}, {"$set": {"mtAction":1,"mtDegree":0}})
    
    print("Successfully recieve motor command. Then we should get going straight command again")
    while True:
        motor4 = collection.find_one({"name": "motor4"})
        if motor4['mtAction'] == 2:
            break
        else:
            time.sleep(0.1)
    collection.update_one({"name":"motor4"}, {"$set": {"mtAction":11,"mtDegree":0}})
    print("Successful! Test case 5")
    
    
    # Test Case 6
    print("Adjusting 30 degrees right interrupt comes from pixy4")
    collection.update_one({"name":"pixy4"}, {"$set": {"piDir":2, "piDegree":30}})
    print("Rover 4 should gets turning right 30 degree command")
    while True:
        motor4 = collection.find_one({"name": "motor4"})
        if motor4['mtAction'] == 8:
            break
        else:
            time.sleep(0.1)
    if motor4['mtDegree'] != 30:return
	
    time.sleep(2)
    collection.update_one({"name":"pixy4"}, {"$set": {"piDir":0, "piDegree":0}})
    collection.update_one({"name":"motor4"}, {"$set": {"mtAction":1,"mtDegree":0}})
    
    print("Successfully recieve motor command. Then we should get going straight command again")
    while True:
        motor4 = collection.find_one({"name": "motor4"})
        if motor4['mtAction'] == 2:
            break
        else:
            time.sleep(0.1)
    collection.update_one({"name":"motor4"}, {"$set": {"mtAction":11,"mtDegree":0}})
    print("Successful! Test case 6")
    
    # Test Case 7
    print("Arm pixy gives interrupt and rover 4 should stop and arm works")
    collection.update_one({"name":"pixy2"}, {"$set": {"piStart":1}})
    print("Rover 4 should gets turning right 30 degree command")
    while True:
        motor4 = collection.find_one({"name": "motor4"})
        arm = collection.find_one({"name": "arm"})
        if motor4['mtAction'] == 4 and  arm['armAction'] == 3:
            break
        else:
            time.sleep(0.1)
    collection.update_one({"name":"motor4"}, {"$set": {"mtAction":1,"mtDegree":0}})
    time.sleep(2)
    collection.update_one({"name":"arm"}, {"$set": {"armAction":1}})
    print("Finish the first one")
    
    while True:
        motor4 = collection.find_one({"name": "motor4"})
        arm = collection.find_one({"name": "arm"})
        if motor4['mtAction'] == 1 and  arm['armAction'] == 4:
            break
        else:
            time.sleep(0.1)
    time.sleep(2)
    collection.update_one({"name":"arm"}, {"$set": {"armAction":1}})
    
    print("After arm action, motor should move")
    while True:
        motor4 = collection.find_one({"name": "motor4"})
        if motor4['mtAction'] == 2:
            break
        else:
            time.sleep(0.1)
    collection.update_one({"name":"motor4"}, {"$set": {"mtAction":11,"mtDegree":0}})
    print("Successful! Test case 7")
    
    # Test Case 8
    print("Sonar4 gives the interrupt for the third turning")
    collection.update_one({"name":"sonar4"}, {"$set": {"sonarDir":1}})
    while True:
        motor4 = collection.find_one({"name": "motor4"})
        if motor4['mtAction'] == 6:
            break
        else:
            time.sleep(0.1)
	
    time.sleep(2)
    collection.update_one({"name":"sonar4"}, {"$set": {"sonarDir":0}})
    collection.update_one({"name":"motor4"}, {"$set": {"mtAction":1,"mtDegree":0}})
    
    print("Successfully recieve motor command. Then we should get going straight command again")
    while True:
        motor4 = collection.find_one({"name": "motor4"})
        if motor4['mtAction'] == 2:
            break
        else:
            time.sleep(0.1)
    collection.update_one({"name":"motor4"}, {"$set": {"mtAction":11,"mtDegree":0}})
    print("Successful! Test case 8")
    
    
    # Test Case 9
    print("Sonar4 gives the interrupt for the forth turning")
    collection.update_one({"name":"sonar4"}, {"$set": {"sonarDir":1}})
    while True:
        motor4 = collection.find_one({"name": "motor4"})
        if motor4['mtAction'] == 6:
            break
        else:
            time.sleep(0.1)
	
    time.sleep(2)
    collection.update_one({"name":"sonar4"}, {"$set": {"sonarDir":0}})
    collection.update_one({"name":"motor4"}, {"$set": {"mtAction":1,"mtDegree":0}})
    
    print("Successfully recieve motor command. Then we should get going straight command again")
    while True:
        motor4 = collection.find_one({"name": "motor4"})
        if motor4['mtAction'] == 2:
            break
        else:
            time.sleep(0.1)
    collection.update_one({"name":"motor4"}, {"$set": {"mtAction":11,"mtDegree":0}})
    print("Successful! Test case 9")
    collection.update_one({"name":"pixy2"}, {"$set": {"piStart":0}})
    
    #input("Press Enter to continue...")
    
    # Test Case 10
    print("Sonar4 gives the interrupt for the fifth turning")
    collection.update_one({"name":"sonar4"}, {"$set": {"sonarDir":1}})
    while True:
        motor4 = collection.find_one({"name": "motor4"})
        if motor4['mtAction'] == 4:
            break
        else:
            time.sleep(0.1)
	
    print("Successfully rover 4 stop")
    collection.update_one({"name":"motor4"}, {"$set": {"mtAction":1,"mtDegree":0}})

    print("Successful! Test case 11")
    print("Successfully game end!")
    

def printData():
    testFuc()

if __name__ == '__main__':
    printData()

