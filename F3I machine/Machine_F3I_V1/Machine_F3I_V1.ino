#include <LiquidCrystal.h>

/*----------------------------- Init des bouton --------------------------------*/
     
const int BAC1= 22;        // bouton chrono 1 base A
const int BBC1= 26;        // bouton chrono 1 base B
const int BAC2= 24;        // bouton chrono 2 base A
const int BBC2= 28;        // bouton chrono 2 base B
const int ModeC= 44;       // interuteur 2 position Mode 1 ou 2 chronometreur
const int RAZ= 32;         // bouton RAZ
const int Larg= 30;        // bouton largague
const int Essai= 54;       // bouton essais
const int PlanSecu = 34;   // bouton plan de sécurité
boolean StateA1 = HIGH;    // status actuel du bouton A1
boolean StateB1 = HIGH;    // status actuel du bouton B1
boolean StateA2 = HIGH;    // status actuel du bouton A2
boolean StateB2 = HIGH;    // status actuel du bouton B2
boolean StateModeC = HIGH; // status actuel du bouton ModeC
boolean StateRAZ = HIGH;   // status actuel du bouton RAZ
boolean StateLarg = HIGH;  // status actuel du bouton Larg
boolean StateEssai = HIGH; // status actuel du bouton Essai
boolean StatePlanSecu = HIGH; // status actuel plan de secu
boolean PrevStateA1 = HIGH;     // status précédént du bouton A1
boolean PrevStateB1 = HIGH;     // status précédént du bouton B1
boolean PrevStateA2 = HIGH;     // status précédént du bouton A2
boolean PrevStateB2 = HIGH;     // status précédént du bouton B2
boolean PrevStateRAZ = HIGH;    // status précédént du bouton Raz
boolean PrevStateLarg = HIGH;   // status précédént du bouton Larguague
boolean PrevStateEssai = HIGH;  // status précédent du bouton Essais
boolean PrevStatePlanSecu = HIGH; // status précédent du bouton plan de secu

/*--------------------------------Init des sortie -----------------------------*/

const int Klaxon = 2;     // Klaxon
const int KB = 10; // sortie klaxon base
const int KE = 11; // sortie klaxon error
const int Kessai = 12; // sortie klaxon essai

/*--------------------------------Init LCD-------------------------------------*/

LiquidCrystal lcd(40, 41, 42, 43, 44, 45);      // Init les pins du LCD

/*--------------------------------Init variable---------------------------------*/

boolean StartVitesseC1 = LOW;  // Vitesse demarré par le concurent sur C1
boolean StartVitesseC2 = LOW;  // Vitesse demarré par le concurent sur C2
boolean FinVitesseC1 = LOW;    // Fin vitesse par le concourent sur C1
boolean FinVitesseC2 = LOW;    // Fin vitesse par le concourent sur C2
boolean HorsTemps = LOW;     // Si concurent est hors temps
boolean PassageAC1 = LOW;    // Passage a la base A pour le chrono 1
boolean PassageAC2 = LOW;    // Passage a la base A pour le chrono 1
boolean PassageBC1 = LOW;    // Passage a la base A pour le chrono 1
boolean PassageBC2 = LOW;    // Passage a la base A pour le chrono 1
boolean BIPB = LOW;          // Son klaxon Base
boolean BIPE = LOW;          // Son klaxon Error
boolean affichage = LOW;     // Autorise l'affichage sur l'ecran de 
boolean PlanDeSecu = LOW;    // Plan de secu
boolean Larguer = LOW;       // Planeur Larguer 

int Nbtour = 4;   // nombre de passage de base a affectuer
int LAP1 = 0;     //compte le nombre de passage en base A et B pour chrono 1
int LAP2 = 0;     //compte le nombre de passage en base A et B pour chrono 2
int NbEssais = 0;  //compte le nombre d'essais du concurent
int toto = 0;

unsigned long startChrono1 = 0;       // temps de démarage chrono 1
unsigned long startChrono2 = 0;       // temps de démarage chrono 2
unsigned long tmpPasseChrono1 = 0;    // temps passé depuis le lancement de chrono 1
unsigned long tmpPasseChrono2 = 0;    // temps passé depuis le lancement de chrono 2
unsigned long tmpPreparation = 0;     // temps de preparation du concurent
unsigned long tmpT1 = 0;              // temps passé depuis le lancement de T1
unsigned long resultChrono1 = 0;      // resultat chrono 1
unsigned long resultChrono2 = 0;      // resultat chrono 2
unsigned long MoyenneChrono = 0;      // Moyenne chrono 1 et chrono 2
unsigned long T1 = 0;                 // Chrono T1
unsigned long T2 = 0;                 // chrono T2
unsigned long BIPBTime = 0;           // Longeur du BIP base
unsigned long BIPETime = 0;           // Longeur du BIP erreur
unsigned long centC1 = 0;             // afficher les centieme de chrono 1
unsigned long secC1=0;                // seconds les sec de chrono 1
unsigned long centC2 = 0;             // afficher les centieme de chrono 2
unsigned long secC2=0;                // seconds les sec de chrono 2
unsigned long centM = 0;              // afficher les centieme de Moyenne
unsigned long secM=0;                 // seconds les sec de Moyenne
unsigned long minT1=0;                // minute pares largage
unsigned long secT1=0;                // seconds largage
unsigned long finalresultChrono1 = 0; // resultat final chrono1
unsigned long finalresultChrono2 = 0; // Resultat final chrono2
unsigned long DelayKlaxon = 0;         // delay buzer

void setup()
{
/*--------------------------------Declaration des input--------------------------*/
  pinMode(BAC1, INPUT);    // declaration comme input le bouton chrono 1 base A
  pinMode(BBC1, INPUT);    // declaration comme input le bouton chrono 1 base B
  pinMode(BAC2, INPUT);    // declaration comme input le bouton chrono 2 base A
  pinMode(BBC2, INPUT);    // declaration comme input le bouton chrono 2 base B
  pinMode(ModeC, INPUT);   // declaration comme input l'interuteur 2 position Mode 1 ou 2 chronometreur
  pinMode(RAZ, INPUT);     // declaration comme input le bouton RAZ
  pinMode(Larg, INPUT);    // declaration comme input le bouton Larguage
  pinMode(Essai, INPUT);   // declaration comme input le bouton Essai
  pinMode(PlanSecu, INPUT); // declaration comme input le bouton plan de secu
  
/*------------------------------Declaration des output --------------------------*/  
  pinMode(Klaxon, OUTPUT);  // declaration comme output du klaxon
  pinMode(KB, OUTPUT);
  pinMode(KE, OUTPUT);
  
/*------------------------------Initialisation Ecran ----------------------------*/
  
  lcd.begin(16, 2);          // Declaration du type d'écran
  lcd.clear();               // Clear l'ecran
  lcd.print("VERSION V0 Proto");   // Displays la version du software 
  delay(3000);                                    
  lcd.clear();
  lcd.setCursor(0,0);        // Place le curseur sur LCD. 1er ligne , 1er place
  lcd.print("C1:");           // Ecrit la legende Ch1: 
  lcd.print("     ");
  lcd.setCursor(8,0);       // Place le curseur sur LCD. 1er ligne , 10eme place
  lcd.print("C2:");           // Ecrit la legende Ch2: 
  lcd.print("     ");
  lcd.setCursor(0,1);        // Place le curseur sur LCD. 2eme ligne , 4eme place
  lcd.print("My:");
  lcd.print("     ");
  lcd.setCursor(8,1);        // Place le curseur sur LCD. 2eme ligne , 4eme place
  lcd.print("Lg:");
  //lcd.print("     ");
}

void loop()
{
/*--------------------------------Lecture de l'état de bouton----------------------*/
  StateA1 = digitalRead(BAC1);        // etat A1
  StateB1 = digitalRead(BBC1);        // etat B1
  StateA2 = digitalRead(BAC2);        // etat A2
  StateB2 = digitalRead(BBC2);        // etat B2
  StateModeC = digitalRead(ModeC);    // etat Mode chrono 1 ou 2 chronometreur
  StateRAZ = digitalRead(RAZ);        // etat bouton RAZ
  StateLarg = digitalRead(Larg);      // etat bouton Larg
  //StateEssai = digitalRead(Essai);    // etat bouton Essai
  StatePlanSecu = digitalRead(PlanSecu); // etat bouton plan de secu

/*------------------------------- Demmare T1 après largage---------------------------*/

if(StateLarg == LOW && StartVitesseC1 == LOW && StartVitesseC2 == LOW && PrevStateLarg == HIGH)
{
  T1 = millis();
  affichage = HIGH;
  PrevStateLarg = HIGH;
  Larguer = HIGH;
}

/*------------------------------- Klaxon après 10 s---------------------------*/

if((millis()-T1 >= 10000) && Larguer == HIGH)
{
  if((millis()-T1 < 11000))
  {
    digitalWrite(Klaxon,HIGH);
  }
  if((millis()-T1 >= 11000))
  {
    digitalWrite(Klaxon,LOW);
  }
}

/*------------------------------- Demarage chrono -----------------------------------*/  
if ((millis()-T1 >= 10000) && Larguer == HIGH)
 {
     if (StartVitesseC1 == LOW && StateA1 == LOW && PrevStateA1 == HIGH)  // Si il y a changement d'état du bouton A1
     {  
     startChrono1= millis();                    // Enregistrement du temps de départ pour le chrono 1
     PrevStateA1 = StateA1;                     // Enregistre l'état de A1 
     //PrevStateA2 = StateA2;                     // Enregistre l'état de A2
     StartVitesseC1 = HIGH;                       // Enregistre que le concurent a demarer la vitesse
     PassageAC1 = HIGH;                         // Enregistre que le concurent est passer a la vitesse A
     affichage = HIGH;                          // autorise l'affichage du chrono
     digitalWrite(Klaxon,HIGH);                 // BIP de passage de la base A Chrono1
     }
     if (StartVitesseC2 == LOW && StateA2 == LOW && PrevStateA2 == HIGH)  // Si il y a changement d'état du bouton A2
     {
     startChrono2= millis();                    // Enregistrement du temps de départ pour le chrono 2
     //PrevStateA1 = StateA1;                     // Enregistre l'état de A1 
     PrevStateA2 = StateA2;                     // Enregistre l'état de A2
     StartVitesseC2 = HIGH;                       // Enregistre que le concurent a demarer la vitesse
     PassageAC2 = HIGH;                         // Enregistre que le concurent est passer a la vitesse B
     affichage = HIGH;                          // autorise l'affichage du chrono
     digitalWrite(Klaxon,HIGH);                 // Bip de passage de la base A chrono2
     }
 }
/*------------------------------------ Comptage des passages -----------------------------*/
 
//Chrono 1:

 if (StartVitesseC1 == HIGH && StateA1 == LOW && PrevStateA1 == HIGH && PassageBC1 == HIGH && LAP1 < 4) // le concurent franchi Base A chrono 1 apres avoir passer B1
  {
    ++LAP1;                      // Ajoute un tour sur chrono 1
    PrevStateA1 = StateA1;       // Enregistre l'état de A1 
    PrevStateB1 = StateB1;       // Enregistre l'état de B1 
    PassageBC1 = LOW;            // prochaine appuit attendu en B chrono 1
    PassageAC1 = HIGH;           // Bloc l'appuit sur A chrono 1
    digitalWrite(Klaxon,HIGH);   // Bip de passage de la base A chrono1
  }
  if(StartVitesseC1 == HIGH && StateB1 == LOW && PrevStateB1 == HIGH && PassageAC1 == HIGH && LAP1 < 4) // le concurent franchi Base B chrono 1 apres avoir passer A1
  {
    ++LAP1;                     // Ajoute un tour sur chrono 1
    PrevStateA1 = StateA1;      // Enregistre l'état de A1 
    PrevStateB1 = StateB1;      // Enregistre l'état de B1 
    PassageAC1 = LOW;           // prochaine appuit attendu en A chrono 1
    PassageBC1 = HIGH;          // Bloc l'appuit sur B chrono 1
    digitalWrite(Klaxon,HIGH);  // Bip de passage de la base B chrono1
  }

//Chrono 2:
  
if (StartVitesseC2 == HIGH && StateA2 == LOW && PrevStateA2 == HIGH && PassageBC2 == HIGH && LAP2 < 4) // le concurent franchi Base A chrono 2 apres avoir passer B2
  {
    ++LAP2;                     // Ajoute un tour sur chrono 2
    PrevStateA2 = StateA2;      // Enregistre l'état de A2
    PrevStateB2 = StateB2;      // Enregistre l'état de B2
    PassageBC2 = LOW;           // prochaine appuit attendu en A chrono 2
    PassageAC2 = HIGH;          // Bloc l'appuit sur B chrono 2
    digitalWrite(Klaxon,HIGH);  // Bip de passage de la base A chrono2
  }
if(StartVitesseC2 == HIGH && StateB2 == LOW && PrevStateB2 == HIGH && PassageAC2 == HIGH && LAP2 < 4) // le concurent franchi Base B chrono 2 apres avoir passer A2
  {
    ++LAP2;                     // Ajoute un tour sur chrono 2
    PrevStateA2 = StateA2;      // Enregistre l'état de A2
    PrevStateB2 = StateB2;      // Enregistre l'état de B2 
    PassageAC2 = LOW;           // prochaine appuit attendu en A chrono 2
    PassageBC2 = HIGH;          // Bloc l'appuit sur B chrono 2
    digitalWrite(Klaxon,HIGH);  // Bip de passage de la base B chrono2
  }
  
/*------------------------------------- Arret des chrono -------------------------------------*/

  if(StartVitesseC1 == HIGH && LAP1 >= 4 && FinVitesseC1 == LOW) // arret du chrono 1 si on a fait 4 passage devans les bases
  {
    resultChrono1 = millis() - startChrono1;
    FinVitesseC1 = HIGH;
    
  }
  if(StartVitesseC2 == HIGH && LAP2 >= 4 && FinVitesseC2 == LOW) // arret du chrono 2 si on a fait 4 passage devans les bases 
  {
    resultChrono2 = millis() - startChrono2;
    FinVitesseC2 = HIGH;
  }
 if(FinVitesseC1 == HIGH && FinVitesseC2 == HIGH)
   {
     affichage = LOW;
   }

/*---------------------------------- Declaration d'un essai-----------------------------------------------*/

/*---------------------------------- Franchisement du plan de secu ---------------------------------------*/

 
 if(StatePlanSecu == LOW && (StartVitesseC1 == HIGH || StartVitesseC2 == HIGH) && (FinVitesseC1 == LOW || FinVitesseC2 == LOW))
  {
    affichage = LOW;
    lcd.clear();                                   // clear l'affichage sur le LCD
    lcd.setCursor(0,0);                            // Set cursor position on LCD
    lcd.print("Plan de Securiter");                // note la faute du concurent sur l'ecran
    PrevStatePlanSecu = HIGH;
    digitalWrite(Klaxon,HIGH);
    delay(3000);
    digitalWrite(Klaxon,LOW);  
  }  
 
/*----------------------------------hors temps -----------------------------------------------------------*/


if ((millis()-T1 >= 120000) && Larguer == HIGH && StartVitesseC1 == LOW && StartVitesseC2 == LOW && HorsTemps == LOW)
  {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" Hors Temps !");
  affichage = LOW;
  HorsTemps = HIGH;
  digitalWrite(Klaxon,HIGH);
  delay(3000);
  digitalWrite(Klaxon,LOW);
}

/*---------------------------------Affichage du Temps depuis le depart-----------------------------------------*/

    if (affichage == HIGH)
        {
         if(Larguer == HIGH && StartVitesseC1 == LOW && StartVitesseC2 == LOW)
         {
         tmpT1 =   millis() - T1;                        // temps passé depuis le largage
         minT1 = (tmpT1/1000)/60;                        // minute T1 to display
         secT1 = (tmpT1/1000)%60 ;                       // second T1 to display
         lcd.setCursor(13,1);                            // Set cursor position on LCD
           lcd.print(".");
         lcd.setCursor(14,1);                            // Set cursor position on LCD
             if (secT1<10) 
             {
             lcd.print("0");
             }
             lcd.print(secT1);                            // display Seconds
         lcd.setCursor(11,1);
             if (minT1<10)
             {
             lcd.print("0");
             }
             lcd.print(minT1);
         }
         if (StartVitesseC1 == HIGH && FinVitesseC1 == LOW)
         {
           tmpPasseChrono1 =   millis() - startChrono1;   // temps passé depuis le lancement de chrono 1
           centC1 = (tmpPasseChrono1%1000)/10 ;                     //centieme chrono 1 to display
           secC1 = (tmpPasseChrono1/1000)%60 ;                      //second chrono 1 to display
           /*--------------------------display chrono 1 ---------------------------------*/
           lcd.setCursor(5,0);                            // Set cursor position on LCD
           lcd.print(".");
           lcd.setCursor(3,0);                            // Set cursor position on LCD
             if (secC1<10) 
             {
             lcd.print("0");
             }
             lcd.print(secC1);                            // display Seconds
           lcd.setCursor(6,0);                            // Set cursor position on LCD
             if (centC1<10)
             {
             lcd.print("0");
             }
             lcd.print(centC1);                            // Display Hundred
         }
         if (StartVitesseC2 == HIGH && FinVitesseC2 == LOW)
         {
           tmpPasseChrono2 =   millis() - startChrono2;   // temps passé depuis le lancement de chrono 2
           centC2 = (tmpPasseChrono2%1000)/10 ;                     //centieme chrono 2 to display
           secC2 = (tmpPasseChrono2/1000)%60 ;                      //second chrono 2 to display
           /*--------------------------display chrono 2 ---------------------------------*/
           lcd.setCursor(13,0);                            // Set cursor position on LCD
           lcd.print(".");
           lcd.setCursor(11,0);                            // Set cursor position on LCD
             if (secC2<10) 
             {
             lcd.print("0");
             }
             lcd.print(secC2);                            // display Seconds
           lcd.setCursor(14,0);                            // Set cursor position on LCD
             if (centC2<10)
             {
             lcd.print("0");
             }
             lcd.print(centC2);                            // Display Hundred
         }     
      }
/*-------------------------display resultat ---------------------------------------------*/

if (FinVitesseC1 == HIGH && FinVitesseC2 == HIGH)
  {
   MoyenneChrono = (resultChrono1 + resultChrono2)/2;
   centM = (MoyenneChrono%1000)/10 ;                     //centieme to display
   secM = (MoyenneChrono/1000)%60 ;                      //second to display
   lcd.setCursor(5,1);                            // Set cursor position on LCD
   lcd.print(".");
   lcd.setCursor(3,1);                            // Set cursor position on LCD
     if (secM <10) 
       {
       lcd.print("0");
       }
     lcd.print(secM);                            // display Seconds
   lcd.setCursor(6,1);                            // Set cursor position on LCD
     if (centM<10)
       {
       lcd.print("0");
       }
     lcd.print(centM);                            // Display Hundred
   }

/*---------------------------------RAZ---------------------------------------------------*/   

if(StateRAZ == LOW) 
{
  LAP1 = 0;
  LAP2 = 0;
  StateA1 = HIGH;    // status actuel du bouton A1
  StateB1 = HIGH;    // status actuel du bouton B1
  StateA2 = HIGH;    // status actuel du bouton A2
  StateB2 = HIGH;    // status actuel du bouton B2
  StateModeC = HIGH; // status actuel du bouton ModeC
  StateRAZ = HIGH;   // status actuel du bouton RAZ
  StateLarg = HIGH;  // status actuel du bouton Larg
  StateEssai = HIGH; // status actuel du bouton Essai
  StatePlanSecu = HIGH; // status actuel plan de secu
  PrevStateA1 = HIGH;     // status précédént du bouton A1
  PrevStateB1 = HIGH;     // status précédént du bouton B1
  PrevStateA2 = HIGH;     // status précédént du bouton A2
  PrevStateB2 = HIGH;     // status précédént du bouton B2
  PrevStateRAZ = HIGH;    // status précédént du bouton Raz
  PrevStateLarg = HIGH;   // status précédént du bouton Larguague
  PrevStateEssai = HIGH;  // status précédent du bouton Essais
  PrevStatePlanSecu = HIGH; // status précédent du bouton plan de secu
  StartVitesseC1 = LOW;  // Vitesse demarré par le concurent
  FinVitesseC1 = LOW;    // Fin vitesse par le concourent
  StartVitesseC2 = LOW;  // Vitesse demarré par le concurent
  FinVitesseC2 = LOW;    // Fin vitesse par le concourent
  HorsTemps = LOW;     // Si concurent est hors temps
  PassageAC1 = LOW;    // Passage a la base A pour le chrono 1
  PassageAC2 = LOW;    // Passage a la base A pour le chrono 1
  PassageBC1 = LOW;    // Passage a la base A pour le chrono 1
  PassageBC2 = LOW;    // Passage a la base A pour le chrono 1
  BIPB = LOW;          // Son klaxon Base
  BIPE = LOW;          // Son klaxon Error
  affichage = LOW;     // Autorise l'affichage sur l'ecran de 
  PlanDeSecu = LOW;    // Plan de secu
  Larguer = LOW;       // Planeur Larguer
  
  Nbtour = 4;   // nombre de passage de base a affectuer
  LAP1 = 0;     //compte le nombre de passage en base A et B pour chrono 1
  LAP2 = 0;     //compte le nombre de passage en base A et B pour chrono 2
  NbEssais = 0;  //compte le nombre d'essais du concurent
  toto = 0;
  
  startChrono1 = 0;       // temps de démarage chrono 1
  startChrono2 = 0;       // temps de démarage chrono 2
  tmpPasseChrono1 = 0;    // temps passé depuis le lancement de chrono 1
  tmpPasseChrono2 = 0;    // temps passé depuis le lancement de chrono 2
  tmpPreparation = 0;     // temps de preparation du concurent
  resultChrono1 = 0;      // resultat chrono 1
  resultChrono2 = 0;      // resultat chrono 2
  MoyenneChrono = 0;      // Moyenne chrono 1 et chrono 2
  T1 = 0;                 // Chrono T1
  T2 = 0;                 // chrono T2
  BIPBTime = 0;           // Longeur du BIP base
  BIPETime = 0;           // Longeur du BIP erreur
  centC1 = 0;             // afficher les centieme de chrono 1
  secC1=0;                // seconds les sec de chrono 1
  centC2 = 0;             // afficher les centieme de chrono 2
  secC2=0;                // seconds les sec de chrono 2
  centM = 0;              // afficher les centieme de Moyenne
  secM=0;                 // seconds les sec de Moyenne

  lcd.setCursor(0,0);        // Place le curseur sur LCD. 1er ligne , 1er place
  lcd.print("C1:");           // Ecrit la legende Ch1: 
  lcd.print("     ");
  lcd.setCursor(8,0);       // Place le curseur sur LCD. 1er ligne , 10eme place
  lcd.print("C2:");           // Ecrit la legende Ch2: 
  lcd.print("     ");
  lcd.setCursor(0,1);        // Place le curseur sur LCD. 2eme ligne , 4eme place
  lcd.print("My:");
  lcd.print("     ");
  lcd.setCursor(8,1);        // Place le curseur sur LCD. 2eme ligne , 4eme place
  lcd.print("Lg:");
  lcd.print("     ");

}



/*--------------------------------------------------diplay debug-------------------------------------------*/
 /*
    lcd.setCursor(0,1);   
    lcd.print(StateA1);  
    lcd.setCursor(1,1);   
    lcd.print(StateB1);  
    lcd.setCursor(2,1);
    lcd.print(StateA2);
    lcd.setCursor(3,1);
    lcd.print(StateB2);
    lcd.setCursor(4,1);
    lcd.print(StateRAZ);
    lcd.setCursor(5,1);
    lcd.print(StateLarg);
    lcd.setCursor(6,1);
    lcd.print(StatePlanSecu);
    
    lcd.setCursor(7,1);
    lcd.print(LAP1);
    lcd.setCursor(8,1);
    lcd.print(LAP2);
   */
}    
  


