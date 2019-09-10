#File:        clearMongo.py
#Goal:        Deletes the database "ECE4534_test"
#Written by:  Joseph Messou
#Last update: 02/27/2019
#Comments:    Use this before testing the flask server


import pymongo
from pymongo import MongoClient

#Default host and port
client = MongoClient('localhost', 27017)
#Get database "ECE4534_test"
db = client['ECE4534_test']
collection = db['test_collection']

client.drop_database('ECE4534_test')
