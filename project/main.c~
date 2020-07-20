#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "stateMachine.h"

void main(void) 
{
  configureClocks();
  clearScreen(COLOR_GREEN);
  switch_init();
  buzzer_init();
  led_init();
  enableWDTInterrupts();

  lcd_init();
  u_char width = screenWidth, height = screenHeight;
  clearScreen(COLOR_BLACK);
  drawString11x16(42,50, "test", COLOR_PINK, COLOR_BLUE);
  //drawString8x12(20,90,"test2", COLOR_PINK, COLOR_BLUE);
  drawString5x7(50,130,"test2", COLOR_PINK, COLOR_BLUE);
  or_sr(0x18);  // CPU off, GIE on

  for(;;) {
    while(!redrawScreen){
      or_sr(0x10);
      P1OUT = LED_GREEN;
    }
    P1OUT = !LED_GREEN;
    redrawScreen = 0;
  }
}
