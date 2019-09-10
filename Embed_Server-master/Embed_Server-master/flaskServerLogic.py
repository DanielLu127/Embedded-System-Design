#Name:         flaskServerLogic.py
#Written by:   Team10
#For:          ECE 4534, Virginia Tech
#Last update:  04/14/2019
#Comments:     Helper functions for the flask servers
from flask import Flask, jsonify, request, Response
from bson.json_util import dumps
import os
Stat_corRec = 0
Stat_inCorRec = 0
Stat_corReply = 0
Stat_inCorReply = 0
allSeqNum = [0, 0, 0, 0]
Stat_misReq = 0

#########################################################
#                   Response code
#########################################################
SUCCESS=200
CREATED=202
BAD_REQUEST=400
NOT_FOUND=404
#########################################################
#                   Response code - END
#########################################################

# Increase request statistic
def stat_Req_Helper(correctness):
    global Stat_corRec
    global Stat_inCorRec
    if(correctness == True):
        Stat_corRec += 1
    else:
        Stat_inCorRec += 1    
        
# Increase reply statistic
def stat_Reply_Helper(correctness):
    global Stat_corReply
    global Stat_inCorReply
    if(correctness == True):
        Stat_corReply += 1
    else:
        Stat_inCorReply += 1
        
def checkSequence(allSeqNumIndex, seqNum):
    global Stat_misReq
    global allSeqNum
    allSeqNum[allSeqNumIndex] += 1
    if seqNum - allSeqNum[allSeqNumIndex] >= 1:
        #print(seqNum)
        Stat_misReq += (seqNum - allSeqNum[allSeqNumIndex])
        
    allSeqNum[allSeqNumIndex] = seqNum
    #print(allSeqNum)
    #print(Stat_misReq)
    
# /arm: PUT helper function
def put_arm_logic(document_name, collection, seqNum):
    data = request.get_json()
    #print(data)
    stat_Req_Helper(True)
    seq = {"seq":seqNum}
    seq_json = dumps(seq)
    #Add to object or create object if necessary
    if data:
        armAction = data['armAction']
        oldDebug_cursor = collection.find({"name":document_name}).limit(1)
        oldDebug = next(oldDebug_cursor,None)
        if oldDebug:
            collection.update_one({"name":document_name}, {"$set": {"armAction":armAction}})
        else:
            collection.insert_one({"name":document_name,"armAction":armAction})
        stat_Reply_Helper(True)
        return Response(seq_json, status=201, mimetype='application/json')
    else:
        stat_Reply_Helper(False)
        error = {'status': BAD_REQUEST, 'error': 'Bad data for: ' + request.url, 'seq': seqNum}
        return buildError(error["status"],error)
        
# /game: PUT helper function
def put_game_logic(document_name, collection, seqNum):
    data = request.get_json()
    #print(data)
    stat_Req_Helper(True)
    seq = {"seq":seqNum}
    seq_json = dumps(seq)
    #Add to object or create object if necessary
    if data:
        board = data['board']
        collection.update_one({"name":"game"}, {"$set": {"board":board}})
        if board == 3:
            armAction = data['armAction']
            mtAction = data['mtAction']
            mtDegree = data['mtDegree']
            collection.update_one({"name":"arm"}, {"$set": {"armAction":armAction}})
            collection.update_one({"name":"motor3"}, {"$set": {"mtAction":mtAction,"mtDegree":mtDegree}})
        elif board == 4:
            armAction = data['armAction']
            mtAction = data['mtAction']
            mtDegree = data['mtDegree']
            collection.update_one({"name":"arm"}, {"$set": {"armAction":armAction}})
            collection.update_one({"name":"motor4"}, {"$set": {"mtAction":mtAction,"mtDegree":mtDegree}})
        stat_Reply_Helper(True)
        return Response(seq_json, status=201, mimetype='application/json')
    else:
        stat_Reply_Helper(False)
        error = {'status': BAD_REQUEST, 'error': 'Bad data for: ' + request.url, 'seq': seqNum}
        return buildError(error["status"],error)
    
# /pixy2: PUT helper function
def put_pixytwo_logic(document_name, collection, seqNum):
    data = request.get_json()
    #print(data)
    stat_Req_Helper(True)
    seq = {"seq":seqNum}
    seq_json = dumps(seq)
    #Add to object or create object if necessary
    if data:
        piStart = data['piStart']
        oldDebug_cursor = collection.find({"name":document_name}).limit(1)
        oldDebug = next(oldDebug_cursor,None)
        if oldDebug:
            collection.update_one({"name":document_name}, {"$set": {"piStart":piStart}})
        else:
            collection.insert_one({"name":document_name,"piStart":piStart})
        stat_Reply_Helper(True)
        return Response(seq_json, status=201, mimetype='application/json')
    else:
        stat_Reply_Helper(False)
        error = {'status': BAD_REQUEST, 'error': 'Bad data for: ' + request.url, 'seq': seqNum}
        return buildError(error["status"],error)
        
# /pixy: PUT helper function
def put_pixy_logic(document_name, collection, seqNum):
    data = request.get_json()
    #print(data)
    stat_Req_Helper(True)
    seq = {"seq":seqNum}
    seq_json = dumps(seq)
    #Add to object or create object if necessary
    if data:
        piDir = data['piDir']
        piDegree = data['piDegree']
        x = data['x']
        y = data['y']
        sig = data['sig']
        xlen = data['xlen']
        ylen = data['ylen']
        oldDebug_cursor = collection.find({"name":document_name}).limit(1)
        oldDebug = next(oldDebug_cursor,None)
        if oldDebug:
            collection.update_one({"name":document_name}, {"$set": {"piDir":piDir, "piDegree":piDegree, 'x' : x , 'y' : y , 'sig' : sig, 'xlen' : xlen , 'ylen' : ylen}})
        else:
            collection.insert_one({"name":document_name,"piDir":piDir, "piDegree":piDegree, })
        stat_Reply_Helper(True)
        return Response(seq_json, status=201, mimetype='application/json')
    else:
        stat_Reply_Helper(False)
        error = {'status': BAD_REQUEST, 'error': 'Bad data for: ' + request.url, 'seq': seqNum}
        return buildError(error["status"],error)
    
# /sonar: PUT helper function
def put_sonar_logic(document_name, collection, seqNum):
    data = request.get_json()
    #print(data)
    stat_Req_Helper(True)
    seq = {"seq":seqNum}
    seq_json = dumps(seq)
    #Add to object or create object if necessary
    if data:
        sonarDir = data['sonarDir']
        sonarDis = data['sonarDis']
        oldDebug_cursor = collection.find({"name":document_name}).limit(1)
        oldDebug = next(oldDebug_cursor,None)
        if oldDebug:
            collection.update_one({"name":document_name}, {"$set":{"sonarDir":sonarDir,"sonarDis":sonarDis}})
        else:
            collection.insert_one({"name":document_name,"sonarDir":sonarDir,"sonarDis":sonarDis})
        stat_Reply_Helper(True)
        return Response(seq_json, status=201, mimetype='application/json')
    else:
        stat_Reply_Helper(False)
        error = {'status': BAD_REQUEST, 'error': 'Bad data for: ' + request.url, 'seq': seqNum}
        return buildError(error["status"],error)

# /motor: PUT helper function
def put_motor_logic(document_name, collection, seqNum):
    data = request.get_json()
    #print(data)
    stat_Req_Helper(True)
    seq = {"seq":seqNum}
    seq_json = dumps(seq)
    #Add to object or create object if necessary
    if data:
        mtAction = data['mtAction']
        mtDegree = data['mtDegree']
        oldDebug_cursor = collection.find({"name":document_name}).limit(1)
        oldDebug = next(oldDebug_cursor,None)
        if oldDebug:
            collection.update_one({"name":document_name}, {"$set": {"mtAction":mtAction,"mtDegree":mtDegree}})
        else:
            collection.insert_one({"name":document_name,"mtAction":mtAction,"mtDegree":mtDegree})
        stat_Reply_Helper(True)
        return Response(seq_json, status=201, mimetype='application/json')
    else:
        stat_Reply_Helper(False)
        error = {'status': BAD_REQUEST, 'error': 'Bad data for: ' + request.url, 'seq': seqNum}
        return buildError(error["status"],error)

# /enco: PUT helper function
def put_enco_logic(document_name, collection, seqNum):
    data = request.get_json()
    #print(data)
    stat_Req_Helper(True)
    seq = {"seq":seqNum}
    seq_json = dumps(seq)
    if data:
        mtLeft = data['mtLeft']
        mtRight = data['mtRight']
        oldDebug_cursor = collection.find({"name":document_name}).limit(1)
        oldDebug = next(oldDebug_cursor,None)
        if oldDebug:
            collection.update_one({"name":document_name}, {"$set": {"mtLeft":mtLeft,"mtRight":mtRight}})
        else:
            collection.insert_one({"name":document_name,"mtLeft":mtLeft,"mtRight":mtRight})
        stat_Reply_Helper(True)
        return Response(seq_json, status=201, mimetype='application/json')
    else:
        stat_Reply_Helper(False)
        error = {'status': BAD_REQUEST, 'error': 'Bad data for: ' + request.url, 'seq': seqNum}
        return buildError(error["status"],error)
        

def board_stat_logic(collection, seqNum):
    statData = request.get_json()
    boardName = statData['name']
    reqSend = statData['reqSend']
    corRec = statData['corRec']
    missReply = statData['missReply']
    global Stat_corRec
    global Stat_inCorRec
    
    seq = {"seq":seqNum}
    seq_json = dumps(seq)
    
    serverStatData = {"name":"server","Stat_corRec":Stat_corRec,"Stat_misReq":Stat_misReq,"Stat_corReply":Stat_corReply,"Stat_inCorReply":Stat_inCorReply}
    #Add to object or create object if necessary (server stat)
    if serverStatData:
        server_cursor = collection.find({"name":"server"}).limit(1)
        server = next(server_cursor,None)
        if server:
            collection.update_one({"name":"server"}, {"$set": {"Stat_corRec": Stat_corRec,"Stat_misReq": Stat_misReq,"Stat_corReply": Stat_corReply,"Stat_inCorReply": Stat_inCorReply}})
        else:
            serverStatData["name"] = "server"
            collection.insert_one(serverStatData)
    else:
        error = {'status': BAD_REQUEST, 'error': 'Bad data for: ' + request.url}
    
    
    #Add to object or create object if necessary (board stat)
    if statData:
        oldDebug_cursor = collection.find({"name": boardName}).limit(1)
        oldDebug = next(oldDebug_cursor,None)
        if oldDebug:
            collection.update_one({"name": boardName}, {"$set": {"reqSend": reqSend,"corRec": corRec,"missReply": missReply}})
        else:
            statData["name"] = boardName
            collection.insert_one(statData)
        stat_Req_Helper(True)
        return Response(seq_json, status=201, mimetype='application/json')
    else:
        stat_Req_Helper(False)
        error = {'status': BAD_REQUEST, 'error': 'Bad data for: ' + request.url, 'seq': seqNum}
        return buildError(error["status"],error)
        
def get_game_logic(collection, seqNum):
    arm = getDocument("arm", collection)
    pixy2 = getDocument("pixy2", collection)
    game = getDocument("game", collection)
    if game['board'] == 3:
        motor = getDocument("motor3", collection)
        pixy = getDocument("pixy3", collection)
        sonar = getDocument("sonar3", collection)
    elif game['board'] == 4:
        motor = getDocument("motor4", collection)
        pixy = getDocument("pixy4", collection)
        sonar = getDocument("sonar4", collection)
    else:
        motor = getDocument("motor", collection)
        pixy = getDocument("pixy", collection)
        sonar = getDocument("sonar", collection)
    document = {'seq':seqNum,"armAction":arm['armAction'],"piStart":pixy2['piStart'],"board":game['board'],"mtAction":motor['mtAction'],"mtDegree":motor['mtDegree'],"piDir":pixy['piDir'],"piDegree":pixy['piDegree'],"sonarDir":sonar['sonarDir'],"name":"game"}
    stat_Req_Helper(True)
    if document:
        document_json = dumps(document)
        #Send back HTTP response
        stat_Reply_Helper(True)
        return Response(document_json, status=SUCCESS, mimetype='application/json')
    else:
        stat_Reply_Helper(False)
        return buildError(NOT_FOUND)
        
#Goal:   Get document from the database as an HTTP Response
#Input:
#        -document_name: name of the document (string)
#        -collection: collection to get the document from (collection)
#Output: HTTP response with document or HTTP error
def get_logic(document_name, collection, seqNum):
    document = getDocument(document_name, collection)
    document.update({'seq':seqNum})
    #print(document)
    if document.get("_id"):
        del document["_id"]
        
    stat_Req_Helper(True)
    if document:
        document_json = dumps(document)
        #Send back HTTP response
        stat_Reply_Helper(True)
        return Response(document_json, status=SUCCESS, mimetype='application/json')
    else:
        stat_Reply_Helper(False)
        return buildError(NOT_FOUND)

#Goal:   Get unique document from the database
#Input:
#        -name: name of the document (string)
#        -collection: collection to get the document from
#Output:
#        -document (dict or None if not found)
def getDocument(name, collection):
    #Look for 1 document (there should only be 1 in the database)
    cursor = collection.find({"name": name}).limit(1)
    #You can also use a for loop that will run once
    return  next(cursor,None)

#Send an error
def buildError(status=NOT_FOUND,error=None):
    if error is None:
        error = {'status': status, 'error': 'Not Found: ' + request.url}
	#jsonify returns a flask.Response object
    resp = jsonify(error)
    resp.status_code = status

    return resp
#########################################################
#               OTHER HELPERS - END
#########################################################
