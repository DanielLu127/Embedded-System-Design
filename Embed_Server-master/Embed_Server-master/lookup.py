import time
import pymongo
from pymongo import MongoClient

#Default host and port
client = MongoClient('localhost', 27017)
#Get database "ECE4534_test" (or create it)
db = client['ECE4534_test']
collection = db['collection']

def getDocument(name, collection):
    #Look for 1 document (there should only be 1 in the database)
    cursor = collection.find({"name": name}).limit(1)
    #You can also use a for loop that will run once
    return  next(cursor,None)

def testFuc():
	while True:
		arm = getDocument("arm", collection)
		pixy2 = getDocument("pixy2", collection)
		game = getDocument("game", collection)
		motor3 = getDocument("motor3", collection)
		pixy3 = getDocument("pixy3", collection)
		sonar3 = getDocument("sonar3", collection)
		motor4 = getDocument("motor4", collection)
		pixy4 = getDocument("pixy4", collection)
		sonar4 = getDocument("sonar4", collection)
		print("\n/////////////////////////////////////////////////////////")
		document = {"armAction":arm['armAction'],"piStart":pixy2['piStart'],"board":game['board']}
		print(document)
		document = {"mtAction":motor3['mtAction'],"mtDegree":motor3['mtDegree'],"piDir":pixy3['piDir'],"piDegree":pixy3['piDegree'],"sonarDir":sonar3['sonarDir']}
		print(document)
		document = {"mtAction":motor4['mtAction'],"mtDegree":motor4['mtDegree'],"piDir":pixy4['piDir'],"piDegree":pixy4['piDegree'],"sonarDir":sonar4['sonarDir']}
		print(document)
		print("/////////////////////////////////////////////////////////\n")
		time.sleep(0.5)

def printData():
	testFuc()

if __name__ == '__main__':
	printData()
