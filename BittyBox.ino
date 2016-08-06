 #include "pitches.h"

const int minLEDPin =1;
const int maxLEDPin =8;
const int speaker1Pin = 9;
const int speaker2Pin = 10;
const int gaugePin = 11;
const int buttonPin = 12;

int noteNb=16;

int notes[] = { NOTE_GS3, NOTE_B3,NOTE_DS4, NOTE_GS4, NOTE_B4,NOTE_DS5};

int notesDP[] = { NOTE_GS3, NOTE_B3,NOTE_DS4, NOTE_GS4, NOTE_B4,NOTE_DS5};
  
int melody[] = {
  0,1,2,3,4,5,
  0,1,2,3,4,5,
  0,1,2,2};

int LEDS[] = {
  0,1,2, 6,3,4, 5,0,1,2,6,3,4,5,6,0,1,2,7,7};

int potard;

int speedo=5;
int aigue=1;
int pauseBetweenNotes;
int noteDuration;


int noteDurations[] = {
  1, 1, 1, 1,1, 1 };


int buttonState;
boolean buttonlow=true;
boolean buttonhigh=true;

int randNumber;
int p1;
int p2;
int stock;

boolean quiet=false;

void setup() {
  
  pinMode(buttonPin, INPUT); 
  
  for (int thisPin = 1; thisPin < 9; thisPin++) { 
    pinMode(thisPin, OUTPUT);
  }
  
  randomSeed(analogRead(A1));
  
  pinMode(gaugePin, OUTPUT);
  
  Serial.begin(9600);

}

void loop() {
    
    for (int thisNote = 0; thisNote < noteNb; thisNote++) {
      if(quiet){
        noteDuration = 1000/speedo/noteDurations[melody[thisNote]];
        pauseBetweenNotes = noteDuration * 1.1;
        
        analogWrite(gaugePin,thisNote);
        
        tone(speaker1Pin,notes[melody[thisNote]]*aigue,noteDuration);
        delay(pauseBetweenNotes);
        noTone(speaker1Pin);
        
        tone(speaker2Pin,notes[melody[thisNote]]*aigue/2,noteDuration/2);
        delay(pauseBetweenNotes/2);
        noTone(speaker2Pin);
        
               if(LEDS[thisNote]>maxLEDPin) {
        for (int thisPin = minLEDPin; thisPin <= maxLEDPin; thisPin++) {
            digitalWrite(thisPin, LOW);
         }
      } else {
        digitalWrite(LEDS[thisNote], LOW);
      }
    


      if(LEDS[thisNote]>maxLEDPin) {
        for (int thisPin = minLEDPin; thisPin <= maxLEDPin; thisPin++) {
          digitalWrite(thisPin, HIGH);
        }
      } else {
        digitalWrite(LEDS[thisNote], HIGH);
      }
        
        buttonState = digitalRead(buttonPin);
        
        if (buttonState == HIGH) {
         if (buttonhigh){
         buttonhigh=false;
         buttonlow=true;
        
         for(int i=0; i<6;i++){
            p1=(int) random(0, 6);
            p2=(int) random(0, 6);
            stock=notes[p1];
            notes[p1]=notes[p2];
            notes[p2]=stock;
         }
        
         for(int i=0; i<6; i++){
           stock=(int) random(0,2);
           noteDurations[i]=1*stock+1;
         }
       } else {
         if(buttonlow){
           buttonlow=false;
           buttonhigh=true;
           
           for(int i=0; i<6; i++){
              notes[i]=notesDP[i];
           }
           
           for(int i=0; i<6; i++){
              noteDurations[i]=1;
           }
         }
       }
       

      
     }
      }
     
     potard=analogRead(A0);
     Serial.println(potard);
      if(potard<=2){
        quiet=false;
      } else if (potard<=105){
        quiet=true;
        speedo=4;
        aigue=1;
      } else if (potard<=120){
        quiet=true;
        speedo=4;
        aigue=2;
      } else if (potard<=500){
        quiet=true;
        speedo=4;
        aigue=4;
      } else if (potard<=850){
        quiet=true;
        speedo=10;
        aigue=2;
      } else {
        quiet=true;
        speedo=10;
        aigue=1;
      }
    
      }

}
