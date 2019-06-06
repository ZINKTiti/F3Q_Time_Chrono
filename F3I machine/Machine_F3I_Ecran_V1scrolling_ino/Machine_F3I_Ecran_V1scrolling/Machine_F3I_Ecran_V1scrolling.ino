#include "SPI.h"        
#include "DMD.h"        
#include "TimerOne.h"
#include "Arial_black_16.h"
#include <SoftwareSerial.h>
#include <EEPROM.h>

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
   savetime(120000,BestTimeMemory);   
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
  
  
  if (ValueRx > readtime(0)) 
  {
    textToScroll = "TEMPS: " + String(sec) + "." + String(cent) + "s";
  }
  else
  {
    textToScroll= "Meilleur Temps : " + String(sec) + "." + String(cent) + "s" + " :o)";
    savetime(ValueRx,BestTimeMemory);
  }
  displaydone = false;
  //Serial.println(readtime(BestTimeMemory));
  //Serial.println(textToScroll);
  
}

/*----------------------------------- Save the time in a memory---------------------*/  
void savetime(long time, int adresse){
  int y = 0;
  int buf[4];
  buf[0] = (byte) time;
  buf[1] = (byte) (time >>8);
  buf[2] = (byte) (time >> 16);
  buf[3] = (byte) (time >> 24);
  for(int i = adresse; i <= adresse + 3 ;i++){
    EEPROM.write(i, buf[y]);
    y++;
  }
  /*
  Serial.println("Ecriture");
  Serial.println(buf[0],BIN);
  Serial.println(buf[1],BIN);
  Serial.println(buf[2],BIN);
  Serial.println(buf[3],BIN);
  */
}

/*----------------------------------- Read the time in a memory---------------------*/ 
unsigned long readtime(int readadresse){
  byte buf[4];
  int y = 0;
  unsigned long returnvalue;
  for(int j = readadresse; j <= readadresse + 3 ;j++){
    buf[y] = EEPROM.read(j);
    y++;
  }
  returnvalue = (buf[3]<<24) + (buf[2]<<16 & 0xF000) + (buf[1]<<8 & 0xFF00) + (buf[0]);
  /*
  z = buf[2]<<16 & 0xF000;
  Serial.println(z,BIN);
  Serial.println("Read:");
  Serial.println(buf[0],BIN);
  Serial.println(buf[1],BIN);
  Serial.println(buf[2],BIN);
  Serial.println(buf[3],BIN);
  Serial.println(returnvalue,DEC);
  */
  return returnvalue;
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
