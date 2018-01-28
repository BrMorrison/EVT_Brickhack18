from serverInterface import *
from bbi2c import *
import time


def main():
	
	MaxListSize=8
	charList={}
	DictFormat={'energy':0,'death':False, 'hunger':0,'happiness':0,'present':False}
	for x in range(1,MaxListSize+1):
		charList[x]=DictFormat

	#print(charList)




	#init start
	#Enum Bus return list of chars
	serverAlive=False
	timeout=3
	for x in range(1,timeout):
		serverAlive=pingServer()
		if True == serverAlive:
			break
		time.sleep(1)

	if False == serverAlive:	
		print("ERROR: Unable To Contact Server")
	else :
		print("Found Response From Server")



	#Establish connection with server return bool 

	#if no connection try again
	#init end
	
	#main loop start
	#poll for change by looping through charList and send number of chars on BUS
	#if change then push changes to server
	#poll server for energy 

	#main loop end





if __name__ == '__main__':
  main()
