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
	

def setData(charlist):
	pass

def getData(charlist):
	buffer = StringIO()
	c = pycurl.Curl()
	c.setopt(c.URL, 'http://pycurl.io/')
	c.setopt(c.WRITEDATA, buffer)
	c.perform()
	c.close()

	body = buffer.getvalue()
	# Body is a string in some encoding.
	# In Python 2, we can print it without knowing what the encoding is.
	print(body)
	pass
