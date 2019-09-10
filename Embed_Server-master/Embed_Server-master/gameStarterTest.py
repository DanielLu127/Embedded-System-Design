import time
import pymongo
from pymongo import MongoClient

#Default host and port
client = MongoClient('localhost', 27017)
#Get database "ECE4534_test" (or create it)
db = client['ECE4534_test']
collection = db['collection']

def testFuc():
    collection.update_one({"name":"arm"}, {"$set": {"armAction":1}})
    collection.update_one({"name":"game"}, {"$set": {"board":1}})
    collection.update_one({"name":"motor3"}, {"$set": {"mtAction":1,"mtDegree":0}})
    collection.update_one({"name":"motor4"}, {"$set": {"mtAction":1,"mtDegree":0}})
    input("Press Enter to continue...")
    collection.update_one({"name":"game"}, {"$set": {"board":1}})
    input("Press Enter to continue...")
    collection.update_one({"name":"game"}, {"$set": {"board":1}})
    
def printData():
	testFuc()

if __name__ == '__main__':
	printData()
