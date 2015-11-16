
#include "pitches.h"

// speaker on pin D0, red LED on pin D1, green LED on pin D2
int spkr  = D0;
int red   = D1;
int green = D2;

int wifiStatus(String command); // not sure why but needed up front or doesn't show up in IFTTT
bool isUp = true;

// notes:
int melody[] = {
  NOTE_A6, NOTE_D6
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 3
};

void setup()
{
  pinMode(spkr, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  digitalWrite(spkr, LOW);
  digitalWrite(red, LOW);
  digitalWrite(green, HIGH);  
  Spark.publish("notifyr/announce","Dana Young alert for no internet connectivity");    
  // register the Spark function
  Spark.function("stringTrig", wifiStatus);
}

void loop()
{

  if (isUp == false ) {

    //play UH OH 
    // iterate over the notes in the array:
    for (int thisNote = 0; thisNote < 2; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / noteDurations[thisNote];
      tone(D0, melody[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      int pauseBetweenNotes = noteDuration * 1.50;
      delay(pauseBetweenNotes);
      // stop the tone playing:
      noTone(D0);
    }
    
    // Wait 1 second
    delay(1000); 

    // turn on red LED, turn off green LED
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);        

    // leave red on for 2 seconds
    delay(2000);

    // Turn off red LED
    digitalWrite(red, LOW);

  }
      
  if (isUp == true) {

    //turn off any sound and red LED, turn on green
    digitalWrite(spkr, LOW);
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);        

    // leave it on for 1 second...
    delay(1000);

    // Turn off green LED
    digitalWrite(green, LOW);

    // Wait 1 second
    delay(1000);
	} 

}

// this function automagically shows up in IFTTT
int wifiStatus(String command)
{
  // look for the matching argument "up" or "down"
  if (command == "down") {
    isUp = false;       
  }
 
  if (command == "up") {
    isUp = true;       
  }
        
}
