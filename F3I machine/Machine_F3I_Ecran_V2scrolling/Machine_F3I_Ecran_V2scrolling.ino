#include "SPI.h"        
#include "DMD.h"        
#include "TimerOne.h"
#include "Arial_black_16.h"
#include <SoftwareSerial.h>

/* you can remove the fonts if unused */
#define DISPLAYS_ACROSS 1
#define DISPLAYS_DOWN 1
#define NB_BYTE 1
DMD dmd( DISPLAYS_ACROSS , DISPLAYS_DOWN, NB_BYTE);

boolean stringComplete = false;  // whether the string is complete
String textToScroll = "";        // String to scroll
unsigned long value = 0;
long ValueRx = 0;
int BestTimeMemory = 0;
unsigned long cent = 0;               // afficher les centieme de chrono 1
unsigned long sec = 0;                // seconds les sec de chrono 1
boolean displaydone = false;
long besttime = 100000;

void ScanDMD()
{ 
  dmd.scanDisplayBySPI();
}

void setup()
{
   Timer1.initialize( 5000 );           
   Timer1.attachInterrupt( ScanDMD );  
   dmd.clearScreen( false );
   Serial.begin(9600);   
}

/*--------------------------------------- Drawing the text ------------------------*/
void drawText( String dispString ) 
{
  dmd.clearScreen( false );
  dmd.selectFont( Arial_Black_16 );
  char newString[256];
  int sLength = dispString.length();
  dispString.toCharArray( newString, sLength+1 );
  dmd.drawMarquee( newString , sLength , ( 32*DISPLAYS_ACROSS )-1 ,0,0xFF,0);
  long start=millis();
  long timer=start;
  long timer2=start;
  boolean ret=false;
  while( !ret ){
    if ( ( timer+60 ) < millis() ) {
      ret=dmd.stepMarquee( -1 , 0 );
      timer=millis();
    }
  }
}

/*----------------------------------- Serial Event --------------------------------*/
void serialEvent() {
  String inputserial = "";
  unsigned long test = 0;
  while (Serial.available()) { 
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputserial += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    } 
  }
  ValueRx = inputserial.toInt();
  cent = (ValueRx%1000)/100 ;                    //centieme
  sec = (ValueRx/1000) ;                      //second
  
  Serial.println(ValueRx);
  Serial.println(sec);
  Serial.println(cent);
  
  
  if (ValueRx > besttime) 
  {
    textToScroll = "TEMPS: " + String(sec) + "." + String(cent) + "s";
  }
  else
  {
    textToScroll= "Meilleur Temps : " + String(sec) + "." + String(cent) + "s" + " :o)";
    besttime = ValueRx;
  }
  displaydone = false;
  //Serial.println(textToScroll);
}

void loop()
{
  delay(50);
  if (displaydone == false)
  {
  drawText(textToScroll);
  displaydone = true;
  }
}
