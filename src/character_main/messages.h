/* messages.h
 *  
 *  Andrew Eberhard 
 *  January 27th, 2018
 *  BrickHack2018
 *  
 */

 #define message_size (80)

 char extremely_happy[message_size] = f("I am ecstatic today! Brick hack is so exciting. :-)");
 char pretty_happy[message_size] = f("I am very happy!");
 char medium_happy[message_size] = f("I am happy!");
 char not_so_happy[message_size] = f("Things could be going better. :-(") ;

 char* happyPtr1 = &extremely_happy;
 char* happyPtr2 = &pretty_happy;
 char* happyPtr3 = &medium_happy;
 char* happyPtr4 = &not_so_happy;

 char* happyPtr[4] = {happyPtr1, happyPtr2, happyPtr3, happyPtr4};

 char extremely_energized[message_size] = f("I feel like my processor speed increased tenfold!");
 char very_energized[message_size] = f("I have a lot of energy! Electricity!!!");
 char medium_energy[message_size] = f("My processor is idling! :p");
 char need_energy[message_size] = f("Do I want to do work: NOP. :-/");

 char* energyPtr1 = &extremely_energized;
 char* energyPtr2 = &very_energized;
 char* energyPtr3 = &medium_energy;
 char* energyptr4 = &need_energy;

 char* energyPtr[4] = {energyPtr1, energyPtr2, energyPtr3, energyPtr4};

 char* extremely_full[message_size] = f("Ooh, are all these instructions for me?");
 char* very_full[message_size] = f("Instructions! OM, NOP, NOP, NOP!");
 char* medium_full[message_size] = f("This isn't the largest program I have every stored.");
 char* need_full[message_size] = f("Feed me!");

 char* hungerPtr1 = &extremely_full;
 char* hungerPtr2 = &very_full;
 char* hungerPtr3 = &medium_full;
 char* hungerPtr4 = &need_full;

 char* hungryPtr[4] = {hungerPtr1, hungerPtr2, hungerPtr3, hungerPtr4};

 char* messageArray[3] = [hungryPtr, happyPtr, energyPtr]; 
