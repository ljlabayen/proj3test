#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "buzzer.h"
#include "stateMachineAssembly.h"
#include "lcdutils.h"
#include "lcddraw.h"

char state, switch_state_down, switch_state_changed;
int redrawScreen;

static char switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);	/* if switch down, sense up */
  return p2val;
}

void switch_init()			/* setup switch */
{  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE |= SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
  switch_interrupt_handler();
}

void switch_interrupt_handler() {
  char p2val = switch_update_interrupt_sense();
  if (p2val & SW1 ? 0 : 1){ //used if p2val and SW1 is true (button 1 is pressed)
    state = 1;
    state_advance(1);
    //    or_sr(0x18);
  }
  else if (p2val & SW2 ? 0 : 1){ //used if p2val and SW2 is true (button 2 is pressed)
    state = 2;
    state_advance(2);
    //    or_sr(0x18);
  }
  else if (p2val & SW3 ? 0 : 1){ //used if p2val and SW3 is true (button 3 is pressed)
    state = 3;
    state_advance(3);
    redrawScreen = 1;
    fillRectangle(30,30,40,40,COLOR_YELLOW);
    // or_sr(0x18);
  }
  else if (p2val & SW4 ? 0 : 1){ //used if p2val and SW4 is true (button 4 is pressed)
    state = 4;
    //    clearScreen(COLOR_BLACK);
    drawString11x16(20,50,"test",COLOR_BLUE,COLOR_BLACK);
    __delay_cycles(20000000);
    //    clearScreen(COLOR_BLACK);
    drawString11x16(20,50,"testtest",COLOR_BLUE,COLOR_BLACK);
    redrawScreen = 1;
    state_advance(4);
    // or_sr(0x18);
  }
  //  state_advance(); // call state advance using assigned value to state
  //  drawString8x12(50,50,"testtest",COLOR_BLUE,COLOR_BLACK);
}
