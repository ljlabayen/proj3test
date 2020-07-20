#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

// define musical note and its frequency
#define A3 2273
#define B3 2025
#define G3 2551
#define E3 3033
#define C3 3846
#define C4 1911
#define D4 1703
#define E4 1517
#define F4 1432
#define G4 1276
#define A4 1136
#define B4 1012
#define C5 956

void buzzer_init()
{
    timerAUpmode();		/* used to drive speaker */
    P2SEL2 &= ~(BIT6 | BIT7);
    P2SEL &= ~BIT7; 
    P2SEL |= BIT6;
    P2DIR = BIT6;		/* enable output to speaker (P2.6) */
}

void buzzer_set_period(short cycles) /* buzzer clock = 2MHz.  (period of 1k results in 2kHz tone) */
{
  CCR0 = cycles; 
  CCR1 = cycles >> 1;		/* one half cycle */
}

// simple beep noise
void beep(){
  // array to hold notes for our loop
  int notes[] = {A4, 0};

  // loop through our array of notes until the end
  for(int i = 0; i < sizeof(notes)/sizeof(*notes); i++) {
    buzzer_set_period(notes[i]); // call buzzer_set_period the a single note as parameter
    __delay_cycles(1200000); // delay the program and wait x clock cycles
    }
}
// random set of notes to create a small tune
void randomSong(){
    int notes[] = {A4, 0, A3, 0, E3, 0, G3, 0, F4, 0, A4, 0, A3, 0, E3, 0, G3, 0, F4, 0};
    
    for(int i = 0; i < sizeof(notes)/sizeof(*notes); i++) {
      buzzer_set_period(notes[i]);
      __delay_cycles(1200000);
    }
}
// method to play a short clip of the baby shark song
void sharkSong(){
  int notes[] = {C5,C5,C5,C5,0,0,D4,D4,0,0,F4,0,0,0,F4,0,F4,0,F4,0,F4,0,F4,0,F4,0,F4,0,0,0};

  for(int i = 0; i < sizeof(notes)/sizeof(*notes); i++) {
    buzzer_set_period(notes[i]);
    __delay_cycles(1200000);
  }
}
// method to play the last part of the spongebob squarepants theme song
void spongebobSong(){
  int notes[] = {G3,0,A4,0,B3,0,A4,0,0,B4,G3,0,0,D4,G3,0};
  
  for(int i = 0; i < sizeof(notes)/sizeof(*notes); i++) {
    buzzer_set_period(notes[i]);
    __delay_cycles(2000000);
  }
}
// method to play an old cellphone ring tone
void errorSong(){
  int notes[] = {E4,0,E4,0,C5,0,C5,B4,B4,500,0};

  for(int i = 0; i < sizeof(notes)/sizeof(*notes); i++) {
    buzzer_set_period(notes[i]);
    __delay_cycles(300000);
  }  
}
