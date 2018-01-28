from lib.Adafruit_I2C import *


def getMCData(MAX_LIST_SIZE):#TODO:add for loops
	GET=0x01
	i2c = Adafruit_2C(deviceID)
	for x in range(1, MAX_LIST_SIZE+1):
		dataDict[x]={'energy':0,'death':False, 'hunger':0,'happiness':0,'msg':0}
		dataDict[x]['energy']=readS8(deviceID,GET)
		dataDict[x]['happiness']=readS8(deviceID,GET)
		dataDict[x]['hunger']=readS8(deviceID,GET)
		dataDict[x]['death']=readS8(deviceID,GET)
		dataDict[x]['msg']=readS8(deviceID,GET)
	return dataDict

def setMCData(dataDict,MAX_LIST_SIZE):
	i2c = Adafruit_I2C(deviceID)
	REBIRTH=0x04
	TRUE=0x01
	FALSE=0x00

	#TODO: ADD IN rebirth once server is working

	busPop=getBusPop(dataDict)

	for deviceID in range(1, MAX_LIST_SIZE+1):

		write8(deviceID,dataDict[x]['energy'])
		write8(deviceID,dataDict[x]['happiness'])
		write8(deviceID,dataDict[x]['hunger'])
		write8(deviceID,busPop)

	return dataDict


def getBusPop(dataDict, MAX_LIST_SIZE):
	NO_DEVICE=0
	busPop=0
	for deviceID in range(1, MAX_LIST_SIZE+1):
		if dataDict[x]['energy'] != NO_DEVICE:
			busPop=busPop+1
	return busPop

