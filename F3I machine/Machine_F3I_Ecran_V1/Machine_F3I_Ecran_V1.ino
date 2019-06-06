#include "SPI.h"      
#include "DMD.h" 
#include "TimerOne.h"
#include "Arial_black_16.h"<arial_black_16.h> 
// you can remove the fonts if unused
#include "SystemFont5x7.h"
#define DISPLAYS_ACROSS 1   
#define DISPLAYS_DOWN 1       
/* change these values if you have more than one DMD connected */
DMD dmd(DISPLAYS_ACROSS,DISPLAYS_DOWN,1);

void ScanDMD()
{ 
  dmd.scanDisplayBySPI();
}

void setup()
{
  Timer1.initialize( 5000 );           
  /*period in microseconds to call ScanDMD. Anything longer than 5000 (5ms) and you can see flicker.*/

  Timer1.attachInterrupt( ScanDMD );  
  /*attach the Timer1 interrupt to ScanDMD which goes to dmd.scanDisplayBySPI()*/

  dmd.clearScreen( false );            
  /* true is normal (all pixels off), false is negative (all pixels on) */
}

void loop()
{
  dmd.selectFont(Arial_Black_16);
  dmd.drawString(1,1,"32.3",4,0xFF,0);
  //dmd.scrollHorz(4,false);
}

