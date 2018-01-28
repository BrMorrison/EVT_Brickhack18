import os
import pycurl
from StringIO import StringIO


def pingServer():
	hostname = "google.com" #TODO: Change this to the real Host
	response = os.system("ping -c 1 " + hostname + "")
	if 0 == response:
		return True
	else:
		return False
	

def setWebData(charlist,MAX_LIST_SIZE):
	pass

def getWebData(charlist,MAX_LIST_SIZE):
	hostname= 'google.com'
	buffer = StringIO()
	c = pycurl.Curl()
	c.setopt(c.URL, hostname+'/'+'')#TODO add in 
	c.setopt(c.WRITEDATA, buffer)
	c.perform()
	c.close()

	body = buffer.getvalue()
	# Body is a string in some encoding.
	# In Python 2, we can print it without knowing what the encoding is.
	print(body)
	pass


# example localhost:5000/new_char?id=1&hunger=50&happiness=25&energy=2
