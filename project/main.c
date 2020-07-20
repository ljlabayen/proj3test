#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "stateMachine.h"

void drawBackground(){
  clearScreen(COLOR_BLUE);
  //test shape
  int j;
  for (int i=110; i<160; i++){
    for (j=0; j < i; j++)
      drawPixel(j,i,COLOR_FOREST_GREEN);
  }
  //right wall
  for (j=110; j<130; j++){
    for(int k=0; k<j; k++)
      drawPixel(j,k,COLOR_NAVY);
  }
  drawRectOutline(25,20,60,50, COLOR_GOLD);
  fillRectangle(27,22,57,47, COLOR_YELLOW);

}
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

  drawBackground();
  
  drawString11x16(32,50, "test", COLOR_PINK, COLOR_BLUE);
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
