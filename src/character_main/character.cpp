/* character.cpp
 *  
 *  Andrew Eberhard 
 *  January 27th, 2018
 *  BrickHack2018
 *  
 */

#include "character.h"
#include <String.h>

#define FullHunger (100)
#define FullHappiness (100)
#define FullEnergy (100)
#define MaxDeath (10000)

enum state {HUNGER = 0, HAPPINESS, ENERGY};

//constructor for i2c slave id
character::character(unsigned char deviceID)
 :i2c_id(deviceID), deathCNT(0), faceNo(deviceID) 
 {
    rebirth();
  }
/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/

void character::rebirth()
{
  set_energy(100);
  set_happiness(100);
  set_hunger(100);
  set_cmd(0x00);
  setLifeTrue();
}

/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/

/*i2c functions*/
unsigned char character::get_id() {return i2c_id;}
void character::set_id(unsigned char deviceID) { i2c_id = deviceID;}

/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/

/*Energy Attributes */
unsigned int character::get_energy() { return energy;}
void character::set_energy(unsigned int energyValue) { energy = energyValue; }

void character::add_energy()
{
  if (get_life())
  {
    if (energy == FullEnergy)
    {
      energy = energy;
    }

    else
    {
      energy++;
    }
  }
}

void character::takeAway_energy()
{
  if (energy == 0)
  {
    setLifeFalse(); //character is dead
  }

  else
  {
    energy--;
  }
}

/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/

/*Hunger Attributes */
unsigned int character::get_hunger() {return hunger;}
void character::set_hunger(unsigned int hungriness) { hunger = hungriness; }

void character::add_hunger()
{
  if (get_life())
  {
    if (hunger == FullHunger){
      hunger = hunger;
    }
    else{
      hunger++;
    }
  }
}

void character::takeAway_hunger()
{
  if (hunger == 0)
  {
    setLifeFalse(); // character is dead;
  }
  else{
    hunger--;
  }
}

/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/

/*Happiness Attributes*/
unsigned int character::get_happiness() { return happiness; }
void character::set_happiness (unsigned int happy) { happiness = happy; }

void character::add_happiness()
{
  if (happiness == FullHappiness)
  {
    happiness = happiness;
  }
  else
  {
    happiness++;
  }
}

void character::takeAway_happiness()
{
  if (happiness == 0)
  {
    takeAway_energy();
  }

  else
  {
    happiness--;
  }
}

void character::takeAway_happinessII(unsigned int decrement)
{
  if (happiness == 0)
  {
    takeAway_energy();
  }
  else
  {
    happiness -= decrement;
  }
}

/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/

/*Life Functions*/
void character::setLifeFalse() 
{
  life = false;
  increaseDeathCNT();
  set_hunger(0);
  set_happiness(0);
  set_energy(0);
}
void character::setLifeTrue() {life = true;}
bool character::get_life() {return life;}


/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/

/*DeathCNT functions */
unsigned int character::get_deathCNT()
{
  return deathCNT;
}

void character::reset_deathCNT()
{
  deathCNT = 0;
}

void character::increaseDeathCNT()
{
  if (deathCNT == MaxDeath)
  {
    reset_deathCNT();
  }
  else
  {
    deathCNT++;
  }
}

/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/

/*faceNo functions */

unsigned int character::get_faceNo() { return faceNo; }
void character::set_faceNo(unsigned int face) {faceNo = face;}

/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/

/*cmd functions */
unsigned char character::get_cmd() { return cmd; }
void character::set_cmd(unsigned char command) {cmd = command;}



/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/

/* message functions */
void character::update_message()
{
  state precedence;
  if (get_hunger() < get_energy())
  {
      if (get_hunger() < get_happiness())
      {
        precedence = HUNGER;
      }

      else if (get_happiness() < get_energy())
      {
        precedence = HAPPINESS;
      }
  }

  else if (get_energy() < get_happiness())
  {
    precedence = ENERGY;
  }

  else
  {
    precedence = HAPPINESS;
  }

  switch (precedence)
  {
    case HUNGER:
      switch(get_hunger() / 25)
      {
        case 0:
          set_message(0b00010001);
          break;
        case 1:
          set_message(0b00010010);
          break;
        case 2:
          set_message(0b00010100);
          break;
        case 3:
          set_message(0b00011000);
          break;
      }
      break;
    case HAPPINESS:
      switch(get_happiness() / 25)
      {
        case 0:
          set_message(0b00100001);
          break;
        case 1:
          set_message(0b00100010);
          break;
        case 2:
          set_message(0b00100100);
          break;
        case 3:
          set_message(0b00101000);
          break;
        }
      break;
    case ENERGY:
      switch(get_energy() / 25)
      {
        case 0:
          set_message(0b01000001);
          break;
        case 1:
          set_message(0b01000010);
          break;
        case 2:
          set_message(0b01000100);
          break;
        case 3:
          set_message(0b01001000);
          break;
      }
    break;
  } 
}

void character::set_message(char message_choice)
{
  message = message_choice;
}

char character::get_message()
{
  return message;
}

