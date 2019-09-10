#Name:         flaskServer.py
#Goal:         Run a flask server at a fixed address/port
#Written by:   Xuan Li
#For:          Team 10
#Last update:  
#Comments:     Address: localhost / Port: 5000
#              Database: localhost:27017

from flask import Flask
app = Flask(__name__)
import pymongo
from pymongo import MongoClient
from flaskServerLogic import *

#Default host and port
client = MongoClient('localhost', 27017)
#Get database "ECE4534_test" (or create it)
db = client['ECE4534_test']
collection = db['collection']

#########################################################
#                   APP ROUTES - START
#########################################################
#Test your app with this (home)
@app.route("/")
def hello():
    return "Hello World!"
    
@app.route("/arm/<int:seqNum>", methods=['GET', 'PUT'])
def armRoutine(seqNum):
    checkSequence(0, seqNum)
    if request.method == 'GET':
        return get_logic("arm", collection, seqNum)
    elif request.method == 'PUT':
        return put_arm_logic("arm", collection, seqNum)
        
@app.route("/game/<int:seqNum>", methods=['GET', 'PUT'])
def gameRoutine(seqNum):
    checkSequence(1, seqNum)
    if request.method == 'GET':
        return get_game_logic(collection, seqNum)
    elif request.method == 'PUT':
        return put_game_logic("game", collection, seqNum)
        
@app.route("/pixy2/<int:seqNum>", methods=['GET', 'PUT'])
def pixytwoRoutine(seqNum):
    checkSequence(1, seqNum)
    if request.method == 'GET':
        return get_logic("pixy2", collection, seqNum)
    elif request.method == 'PUT':
        return put_pixytwo_logic("pixy2", collection, seqNum)
        
@app.route("/pixy3/<int:seqNum>", methods=['GET', 'PUT'])
def pixythreeRoutine(seqNum):
    checkSequence(2, seqNum)
    if request.method == 'GET':
        return get_logic("pixy3", collection, seqNum)
    elif request.method == 'PUT':
        return put_pixy_logic("pixy3", collection, seqNum)
        
@app.route("/pixy4/<int:seqNum>", methods=['GET', 'PUT'])
def pixyfourRoutine(seqNum):
    checkSequence(3, seqNum)
    if request.method == 'GET':
        return get_logic("pixy4", collection, seqNum)
    elif request.method == 'PUT':
        return put_pixy_logic("pixy4", collection, seqNum)
        
@app.route("/sonar3/<int:seqNum>", methods=['GET', 'PUT'])
def sonarthreeRoutine(seqNum):
    checkSequence(2, seqNum)
    if request.method == 'GET':
        return get_logic("sonar3", collection, seqNum)
    elif request.method == 'PUT':
        return put_sonar_logic("sonar3", collection, seqNum)
        
@app.route("/sonar4/<int:seqNum>", methods=['GET', 'PUT'])
def sonarfourRoutine(seqNum):
    checkSequence(3, seqNum)
    if request.method == 'GET':
        return get_logic("sonar4", collection, seqNum)
    elif request.method == 'PUT':
        return put_sonar_logic("sonar4", collection, seqNum)

@app.route("/motor3/<int:seqNum>", methods=['GET', 'PUT'])
def motorRoutine(seqNum):
    checkSequence(2, seqNum)
    if request.method == 'GET':
        return get_logic("motor3", collection, seqNum)
    elif request.method == 'PUT':
        return put_motor_logic("motor3", collection, seqNum)
        
@app.route("/motor4/<int:seqNum>", methods=['GET', 'PUT'])
def motorRoutines(seqNum):
    checkSequence(3, seqNum)
    if request.method == 'GET':
        return get_logic("motor4", collection, seqNum)
    elif request.method == 'PUT':
        return put_motor_logic("motor4", collection, seqNum)
        
@app.route("/enco/<int:seqNum>", methods=['PUT'])
def encoRoutine(seqNum):
    checkSequence(0, seqNum)
    if request.method == 'PUT':
        return put_enco_logic("enco", collection, seqNum)
        
@app.route("/stat0/<int:seqNum>", methods=['PUT'])
def stat0(seqNum):
    checkSequence(0, seqNum)
    if request.method == 'PUT':
        return board_stat_logic(collection, seqNum)

@app.route("/stat1/<int:seqNum>", methods=['PUT'])
def stat1(seqNum):
    checkSequence(1, seqNum)
    if request.method == 'PUT':
        return board_stat_logic(collection, seqNum)
        
@app.route("/stat2/<int:seqNum>", methods=['PUT'])
def stat2(seqNum):
    checkSequence(2, seqNum)
    if request.method == 'PUT':
        return board_stat_logic(collection, seqNum)
        
@app.route("/stat3/<int:seqNum>", methods=['PUT'])
def stat3(seqNum):
    checkSequence(3, seqNum)
    if request.method == 'PUT':
        return board_stat_logic(collection, seqNum)

@app.errorhandler(404)
def not_found(error=None):
    stat_Req_Helper(False)
    stat_Reply_Helper(False)
    return buildError(404)

@app.errorhandler(400)
def not_found(error=None):
    stat_Req_Helper(False)
    stat_Reply_Helper(False)
    return buildError(400)

#########################################################
#                    APP ROUTES - END
#########################################################


if __name__ == '__main__':
    app.run(debug = True,host='localhost',port = 5000)
    #app.run(debug = True, host = 'localhost', port = 5000, threaded=True)
