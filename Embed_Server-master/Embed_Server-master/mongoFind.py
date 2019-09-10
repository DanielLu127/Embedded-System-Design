import threading
import pymongo
from pymongo import MongoClient
from flaskServer import *

#Default host and port
client = MongoClient('localhost', 27017)
#Get database "ECE4534_test" (or create it)
db = client['ECE4534_test']

def queryData():
#	B1 = collection.find_one({"name": "test"})
#	B2 = collection.find_one({"name": "testSum"})
	B1_cursor = collection.find({"name": "B1"}).limit(1)
	B1 = next(B1_cursor,None)
	
	B2_cursor = collection.find({"name": "B2"}).limit(1)
	B2 = next(B2_cursor,None)

	B3_cursor = collection.find({"name": "B3"}).limit(1)
	B3 = next(B3_cursor,None)
	
	B4_cursor = collection.find({"name": "B4"}).limit(1)
	B4 = next(B4_cursor,None)
	
	server_cursor = collection.find({"name": "server"}).limit(1)
	server = next(server_cursor,None)
	
	if B1:
		print("Board 1 =================================================")
		print("Number of requests send: " + str(B1['reqSend']))
		print("Number of correct replies received: " + str(B1['corRec']))
		print("Number of missed replies: " + str(B1['missReply']))
		print()
	else:
		print("Missing Data From Board1")
		print()
	if B2:
		print("Board 2 =================================================")
		print("Number of requests send: " + str(B2['reqSend']))
		print("Number of correct replies received: " + str(B2['corRec']))
		print("Number of missed replies: " + str(B2['missReply']))
		print()
	else:
		print("Missing Data From Board2")
		print()
	if B3:
		print("Board 3 =================================================")
		print("Number of requests send: " + str(B3['reqSend']))
		print("Number of correct replies received: " + str(B3['corRec']))
		print("Number of missed replies: " + str(B3['missReply']))
		print()
	else:
		print("Missing Data From Board3")
		print()
	if B4:
		print("Board 4 =================================================")
		print("Number of requests send: " + str(B4['reqSend']))
		print("Number of correct replies received: " + str(B4['corRec']))
		print("Number of missed replies: " + str(B4['missReply']))
		print()
	else:
		print("Missing Data From Board4")
		print()
		
	if server:
		print("Server ==================================================")
		print("Number of correct requests received: " + str(server['Stat_corRec']))
		print("Number of missed requests: " + str(server['Stat_misReq']))
		print("Number of correct replies sent: " + str(server['Stat_corReply']))
		print("Number of incorrect replies sent: " + str(server['Stat_inCorReply']))
		print()
	else:
		print("Missing Data From Server")
		print()


def printData():
	threading.Timer(2.0, printData).start()
	queryData()
	

if __name__ == '__main__':
	printData()
