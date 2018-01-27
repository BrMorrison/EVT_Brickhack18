#include "wire.h"
#include "character.h"

#define message_size (80)
#define status_bytes (5)
#define max_data_bytes (85)

#define slave_address (0x01)

#define status_cmd (0x01)
#define rebirth_cmd (0x02)

void setup()
{
  
  //put setup code here
  Character character1(slave_address);  //create character for arduino 
  Wire.begin(slave_address);      //intitialize i2c communications with slave_address
  Wire.onReceive(receiveEvent);   //register receive event
  Wire.onRequest(requestEvent);   //register transmit event
  Serial.begin(9600);
}

void loop()
{
}

void receiveEvent()
{
  //data to be received
  // -command byte (0xff = rebirth, 0x00 = happiness++)
}

void requestEvent()
{
  unsigned int = 0; 
  char data_to_be_sent[max_data_bytes];
  
  data_to_be_sent[0] = (char) character1.get_energy();
  data_to_be_sent[1] = (char) character1.get_happiness();
  data_to_be_sent[2] = (char) character1.get_hunger();
  data_to_be_sent[3] = (char) character1.get_faceNo();
  data_to_be_sent[4] = (char) character1.get_life();

  while (character1.get_messageByte[i] != '\0');
  {
    
  }
  
    
  Wire.write(data_to_be_sent, data_bytes);
}

