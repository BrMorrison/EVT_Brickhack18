from serverInterface import *
from bbi2c import *
import time

#ENABLE WHEN ON BB
BB =True
WEB=False

def main():
	


	#init start
	MAX_LIST_SIZE=8
	charList={}
	#DictFormat={'energy':0,'death':False, 'hunger':0,'happiness':0,'msg':0}
	#for x in range(1,MaxListSize+1):
	#	charList[x]=DictFormat

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

	#init end
	try:
		while True == True:
			if WEB:
				charList=getWebData(MAX_LIST_SIZE)
			if BB:
				setMCData(charList,MAX_LIST_SIZE)
				charList=getMCData(MAX_LIST_SIZE)
			if WEB:
				setWebData(charList,MAX_LIST_SIZE)
			time.sleep(1)
	except:
		print("\nEXCEPTION, CODE EXIT")



if __name__ == '__main__':
  main()
