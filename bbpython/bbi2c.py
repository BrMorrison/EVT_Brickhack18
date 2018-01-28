from lib.Adafruit_I2C import *

#i2c = Adafruit_I2C(0x77)

cmdDict={'cmd':0x01, 'id':0x01, 'energy':0x02,'deathFlag':0x04,'msgLen':0x08, 'msg':0x0F}




# - get cmd (0x01): 
#- request the status of the arduino (i.e. hunger, happiness, energy, and "tweetable" message);
#-2nd Byte:
#	Char ID Value 0x01
#	Energy Value 0x02
#	Alive Value 0x04
#	Msg length 0x08
#		-Length of message. Null byte if no msg to send
#- set cmds
#	- set/update a value on the arduino
#	- 1st Byte
#		-Hunger 0x02
#		-Happiness 0x04
		
#	- 2nd Byte 
#		-Value of what is specified by first byte