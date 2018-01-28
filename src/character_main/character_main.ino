/* character_main.ino
 *  
 *  Andrew Eberhard 
 *  January 27th, 2018
 *  BrickHack2018
 *  
 */

#include <Wire.h>
#include "character.h"

#define message_size (1)
#define status_bytes (4)
#define max_data_bytes (message_size + status_bytes)

#define slave_address (0x01)

#define status_cmd (0x01)
#define set_value_cmd (0x02)
#define rebirth_cmd (0x04) 

int buttonPin = 2;
int hungerPin = 9;
int deathPin = 4;
unsigned int happyDecrement = 1;

bool firstTime;

char receivedValue[4];

character character1(slave_address);  //create character for arduino   

void setup()
{
  //put setup code here
  Wire.begin(slave_address);      //intitialize i2c communications with slave_address
  Wire.onReceive(receiveEvent);   //register receive event
  Wire.onRequest(requestEvent);   //register transmit event
  Serial.begin(9600);

  pinMode(hungerPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(deathPin, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonPressISR, CHANGE); //active-high button press
}

void loop()
{
  delay(5000); //delay for 30s
  character1.takeAway_hunger();
  character1.takeAway_energy();
  character1.takeAway_happinessII(happyDecrement);
  
  analogWrite(hungerPin, character1.get_hunger());

  if (character1.get_life())
  {
    digitalWrite(deathPin, LOW);
  }

  else
  {
    digitalWrite(deathPin, HIGH);
  }
}

//interrupt service routine
void buttonPressISR()
{
  //user is feeding the hungry microcontroller
  if (digitalRead(hungerPin) == LOW)
  {
    feedByteISR();
  }
}

void feedByteISR()
{
  //add to the hunger of the microcontroller
  character1.add_hunger();
}

void receiveEvent(int howMany)
{
  //data to be received
  // -command byte (0xff = rebirth, 0x00 = happiness++)

  int i = 0;
  char receivedCommand;
      
  receivedCommand = Wire.read();
  character1.set_cmd((unsigned byte) receivedCommand);

  if (character1.get_cmd() == set_value_cmd)
  {
    while (1 < Wire.available())
    {
      receivedValue[i] = Wire.read();
      i++;
    }

    updateStateValues();
    happyDecrement = calculateHappinessDecrement((unsigned int) receivedValue[3]); 
  }

  else if (character1.get_cmd() == rebirth_cmd)
  {
    character1.rebirth();
  }
}

void requestEvent()
{
  unsigned int messageByte = 0; 
  char tempChar;
  char data_to_be_sent[max_data_bytes];
  
  data_to_be_sent[0] = (char) character1.get_energy();
  data_to_be_sent[1] = (char) character1.get_happiness();
  data_to_be_sent[2] = (char) character1.get_hunger();
  data_to_be_sent[3] = (char) character1.get_life();
  data_to_be_sent[4] = (char) character1.get_message();
   
  Wire.write(data_to_be_sent, max_data_bytes);
}

void updateStateValues()
{
  character1.set_energy((unsigned int) receivedValue[0]);
  character1.set_hunger((unsigned int) receivedValue[2]);

  if (firstTime)
  {
    character1.set_happiness((unsigned int) receivedValue[1] );
    firstTime = false;
  }
}

unsigned int calculateHappinessDecrement(unsigned int populationSize)
{
  switch (populationSize)
  {
    case 1:
      return 8;
    case 2:
      return 8;
    case 3:
      return 8;
    case 4:
      return 8;
    case 5: 
      return 4;
    case 6:
      return 2;
    case 7:
      return 1;
    case 8:
      return 0;  
  }
}

