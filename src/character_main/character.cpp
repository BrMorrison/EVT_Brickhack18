/* character.cpp
 *  
 *  Andrew Eberhard 
 *  January 27th, 2018
 *  BrickHack2018
 *  
 */

#include character.h

#define FullHunger (100)
#define FullHappiness (100)
#define FullEnergy (100)
#define MaxDeath (10000)

//constructor for i2c slave id
Character::Character(unsigned byte deviceID)
 :i2c_id(deviceID), deathCNT(0){}
/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/

void character::rebirth()
{
  set_energy(100);
  set_happiness(100);
  set_hunger(100);
  setLifeTrue();
}

/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/

/*i2c functions*/
unsigned byte character::get_id() {return i2c_id;}
void character::set_id(unsigned byte deviceID) { i2c_id = deviceID;}

/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/

/*Energy Attributes */
unsigned int character::get_energy() { return energy;}
void character::set_energy(unsigned int energy) { unsigned int energy = 0; }

void character::add_energy()
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

void character::takeAway_energy()
{
  if (energy = 0)
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
void character::set_hunger(unsigned int hungriness) { hunger = hungriness }

void add_hunger()
{
  if (hunger == FullHunger){
      hunger = hunger;
    }
  else{
      hunger++;
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

/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/

/*Life Functions*/
void character::setLifeFalse() 
{
  life = false;
  increaseDeathCNT();
}
void character::setLifeTrue() {life = true;}
bool character::getLife() {return life;}


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

void increaseDeathCNT()
{
  if (deathCNT == MaxDeath)
  {
    resetDeathCNT;
  }
  else
  {
    deathCNT++;
  }
}

