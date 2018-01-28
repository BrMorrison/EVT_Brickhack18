
import os


def pingServer():
	hostname = "google.com" #example
	response = os.system("ping -c 1 " + hostname + "")
	if 0 == response:
		return True
	else:
		return False
	

def setData(charlist):
	pass

def getData(charlist):
	pass
