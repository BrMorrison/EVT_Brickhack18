#include <Wire.h>
#include "character.h"


#define message_size (80)
#define status_bytes (4)
#define max_data_bytes (message_size + status_bytes)

#define slave_address (0x01)

#define status_cmd (0x01)
#define rebirth_cmd (0x02)
#define happiness_cmd (0x03)
#define energy_cmd (0x04)

int buttonPin = 2;
int hungerPin = 9;
int deathPin = 4;
int newMemberPin = 7;

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
  pinMode(newMemberPin, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonPressISR, CHANGE); //active-high button press
}

void loop()
{
  delay(100); //delay for 30s
  character1.takeAway_hunger();
  character1.takeAway_energy();
  Serial.println("\n");
  Serial.println(character1.get_hunger());
  Serial.println(character1.get_energy());
  
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

  char receivedCommand;
  byte command;

  while (1 < Wire.available())
  {
    receivedCommand = Wire.read();
    character1.set_cmd((unsigned byte) receivedCommand);
  }

  if (character1.get_cmd() == rebirth_cmd)
  {
    character1.rebirth();
  }

  else if (character1.get_cmd() == energy_cmd)
  {
    character1.add_energy();
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

  do
  {
    //tempChar = character1.get_messageByte[i];
    data_to_be_sent[messageByte + status_bytes] = tempChar;
    messageByte++;
  } while (tempChar != '\0');
   
  Wire.write(data_to_be_sent, (messageByte - 1) + status_bytes);
}

