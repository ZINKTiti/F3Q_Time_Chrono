#include <LiquidCrystal.h>

/*----------------------------- Init des bouton --------------------------------*/
     
const int BAC1= 50;        // bouton chrono 1 base A
const int BBC1= 51;        // bouton chrono 1 base B
const int BAC2= 50;        // bouton chrono 2 base A
const int BBC2= 51;        // bouton chrono 2 base B
const int ModeC= 44;       // interuteur 2 position Mode 1 ou 2 chronometreur
const int RAZ= 52;         // bouton RAZ
const int Larg= 53;        // bouton largague
const int Essai= 54;       // bouton essais
const int PlanSecu = 55;   // bouton plan de sécurité
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

const int KB = 10; // sortie klaxon base
const int KE = 11; // sortie klaxon error
const int Kessai = 12; // sortie klaxon essai

/*--------------------------------Init LCD-------------------------------------*/

LiquidCrystal lcd(30, 31, 42, 43, 44, 45);      // Init les pins du LCD

/*--------------------------------Init variable---------------------------------*/

boolean StartVitesse = LOW;  // Vitesse demarré par le concurent
boolean FinVitesse = LOW;    // Fin vitesse par le concourent
boolean HorsTemps = LOW;     // Si concurent est hors temps
boolean PassageAC1 = LOW;    // Passage a la base A pour le chrono 1
boolean PassageAC2 = LOW;    // Passage a la base A pour le chrono 1
boolean PassageBC1 = LOW;    // Passage a la base A pour le chrono 1
boolean PassageBC2 = LOW;    // Passage a la base A pour le chrono 1
boolean BIPB = LOW;          // Son klaxon Base
boolean BIPE = LOW;          // Son klaxon Error
boolean affichage = LOW;     // Autorise l'affichage sur l'ecran
boolean PlanDeSecu = LOW;    // Plan de secu

int Nbtour = 4;   // nombre de passage de base a affectuer
int LAP1 = 0;     //compte le nombre de passage en base A et B pour chrono 1
int LAP2 = 0;     //compte le nombre de passage en base A et B pour chrono 2
int NbEssais = 0;  //compte le nombre d'essais du concurent

unsigned long startChrono1 = 0;       // temps de démarage chrono 1
unsigned long startChrono2 = 0;       // temps de démarage chrono 2
unsigned long tmpPasseChrono1 = 0;    // temps passé depuis le lancement de chrono 1
unsigned long tmpPasseChrono2 = 0;    // temps passé depuis le lancement de chrono 2
unsigned long tmpPreparation = 0;     // temps de preparation du concurent
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
  pinMode(KB, OUTPUT);
  pinMode(KE, OUTPUT);
/*------------------------------Initialisation Ecran ----------------------------*/
  lcd.begin(16, 2);          // Declaration du type d'écran
  lcd.clear();               // Clear l'ecran
  lcd.print("VERSION V0");   // Displays la version du software 
  delay(3000);                                    
  lcd.clear();
  lcd.setCursor(0,0);        // Place le curseur sur LCD. 1er ligne , 1er place
  lcd.print("C1");           // Ecrit la legende Ch1: 
  lcd.print("     ");
  lcd.setCursor(10,0);       // Place le curseur sur LCD. 1er ligne , 10eme place
  lcd.print("C2");           // Ecrit la legende Ch2: 
  lcd.print("     ");
  lcd.setCursor(4,1);        // Place le curseur sur LCD. 2eme ligne , 4eme place
  lcd.print("Moy:");
  lcd.print("     ");
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
  StateEssai = digitalRead(Essai);    // etat bouton Essai
  StatePlanSecu = digitalRead(PlanSecu); // etat bouton plan de secu

/*------------------------------- Demmare T1 après largage---------------------------*/
   if (StateLarg == LOW && PrevStateLarg == HIGH && StartVitesse == LOW && T1 == 0 ) // Vérifie la transition du bouton largage pour demarage T1
   {         
     T1 = millis();                                      // Enregistre le temps dans T1
     PrevStateA1 = StateA1;                              // Enregistre l'état de A1 
     PrevStateA2 = StateA2;                              // Enregistre l'état de A2
     PrevStateLarg = StateLarg;                          // Enregistre l'état actuel de largage
    }
   else if ((millis() - T1 >= 10000) && (millis() - T1) <= 60000 && StartVitesse == LOW) // verfie que T1 est >= a 10s et < 60s et pas encore en vitesse
   {
     affichage = HIGH;                           // autorise l'affichage du chrono
     
     if (StateA1 == LOW && PrevStateA1 == HIGH)  // Si il y a changement d'état du bouton A1
     {  
     startChrono1= millis();                    // Enregistrement du temps de départ pour le chrono 1
     PrevStateA1 = StateA1;                     // Enregistre l'état de A1 
     PrevStateA2 = StateA2;                     // Enregistre l'état de A2                       
     StartVitesse = HIGH;                       // Enregistre que le concurent a demarer la vitesse
     PassageAC1 = HIGH;                         // Enregistre que le concurent est passer a la vitesse A
     }
     if (StateA2 == LOW && PrevStateA2 == HIGH)  // Si il y a changement d'état du bouton A2
     {
     startChrono2= millis();                    // Enregistrement du temps de départ pour le chrono 2
     PrevStateA1 = StateA1;                     // Enregistre l'état de A1 
     PrevStateA2 = StateA2;                     // Enregistre l'état de A2 
     StartVitesse = HIGH;                       // Enregistre que le concurent a demarer la vitesse
     PassageAC2 = HIGH;                         // Enregistre que le concurent est passer a la vitesse B  
     }
    }
    else if ((millis() - T1) > 120000 && StartVitesse == LOW) // si temps pour commencer la tache est depasser de 2 minute soit 120s soit 120000ms
    {
     lcd.clear();                      // Clear l'ecran
     lcd.print("  HORS TEMPS !");      // Affichage du message Hors Temps
     HorsTemps = HIGH;                 // Mise la valeur hors temps a 1
    }

/*------------------------------------ Comptage des passages -----------------------------*/
 
  if(StartVitesse == HIGH && StateB1 == LOW && PrevStateB1 == HIGH && PassageAC1 == HIGH) // le concurent franchi Base B chrono 1 apres avoir passer A1
  {
    ++LAP1;                  // Ajoute un tour sur chrono 1
    PrevStateA1 = StateA1;       // Enregistre l'état de A1 
    PrevStateA2 = StateA2;       // Enregistre l'état de A2
    PrevStateB1 = StateB1;       // Enregistre l'état de B1 
    PrevStateB2 = StateB2;       // Enregistre l'état de B2
    BIPB = HIGH;             // BIP la base
    PassageAC1 = LOW;        // prochaine appuit attendu en A chrono 1
    PassageBC1 = HIGH;       // Bloc l'appuit sur B chrono 1 
  }
  else if (StartVitesse == HIGH && StateB2 == LOW && PrevStateB2 == HIGH && PassageAC2 == HIGH) // le concurent franchi Base B chrono 2 apres avoir passer A2
  {
    ++LAP2;                  // Ajoute un tour sur chrono 2
    PrevStateA1 = StateA1;       // Enregistre l'état de A1 
    PrevStateA2 = StateA2;       // Enregistre l'état de A2
    PrevStateB1 = StateB1;       // Enregistre l'état de B1 
    PrevStateB2 = StateB2;       // Enregistre l'état de B2
    PrevSta 
    BIPB = HIGH;             // BIP la base
    PassageAC2 = LOW;        // prochaine appuit attendu en A chrono 2
    PassageBC2 = HIGH;       // Bloc l'appuit sur B chrono 2 
  }
  else if (StartVitesse == HIGH && StateA1 == LOW && PrevStateA1 == HIGH && PassageBC1 == HIGH) // le concurent franchi Base A chrono 1 apres avoir passer B1
  {
    ++LAP1;                  // Ajoute un tour sur chrono 1
    PrevStateA1 = StateA1;       // Enregistre l'état de A1 
    PrevStateA2 = StateA2;       // Enregistre l'état de A2
    PrevStateB1 = StateB1;       // Enregistre l'état de B1 
    PrevStateB2 = StateB2;       // Enregistre l'état de B2 
    BIPB = HIGH;             // BIP la base
    PassageBC1 = LOW;        // prochaine appuit attendu en B chrono 1
    PassageAC1 = HIGH;       // Bloc l'appuit sur A chrono 1 
  }
  else if (StartVitesse == HIGH && StateA2 == LOW && PrevStateA2 == HIGH && PassageBC2 == HIGH) // le concurent franchi Base A chrono 2 apres avoir passer B2
  {
    ++LAP2;                  // Ajoute un tour sur chrono 2
    PrevStateA1 = StateA1;       // Enregistre l'état de A1 
    PrevStateA2 = StateA2;       // Enregistre l'état de A2
    PrevStateB1 = StateB1;       // Enregistre l'état de B1 
    PrevStateB2 = StateB2;       // Enregistre l'état de B2
    BIPB = HIGH;             // BIP la base
    PassageBC2 = LOW;        // prochaine appuit attendu en A chrono 2
    PassageAC2 = HIGH;       // Bloc l'appuit sur B chrono 2 
  }

/*------------------------------------- Arret des chrono -------------------------------------*/

  if(StartVitesse == HIGH && LAP1 == 4) // arret du chrono 1 si on a fait 4 passage devans les bases
  {
    resultChrono1 = millis() - startChrono1;
    FinVitesse = HIGH;
  }
  if(StartVitesse == HIGH && LAP2 == 4) // arret du chrono 2 si on a fait 4 passage devans les bases 
  {
    resultChrono2 = millis() - startChrono2;
    FinVitesse = HIGH;
  }

/*---------------------------------- BIpe des base -------------------------------------------------------*/

 



/*---------------------------------- Declaration d'un essai-----------------------------------------------*/

/*---------------------------------- Franchisement du plan de secu ---------------------------------------*/

  if(StartVitesse == HIGH && StatePlanSecu == HIGH)  // si le concurent franchi le plan de sécurité durant ca vitesse
  {
    lcd.clear();                                   // clear l'affichage sur le LCD
    lcd.setCursor(0,0);                            // Set cursor position on LCD
    lcd.print("Plan de Securiter");                // note la faute du concurent sur l'ecran
  }


/*---------------------------------Affichage du Temps depuis le depart-----------------------------------------*/

    if (affichage == HIGH)
        {
         tmpPasseChrono1 =   millis() - startChrono1;   // temps passé depuis le lancement de chrono 1
         tmpPasseChrono2 =   millis() - startChrono2;   // temps passé depuis le lancement de chrono 2
         /*--------------------------display chrono 1 ---------------------------------*/
         lcd.setCursor(5,0);                            // Set cursor position on LCD
         lcd.print(":");
         lcd.setCursor(3,0);                            // Set cursor position on LCD
           if (secC1 <10) 
           {
           lcd.print("00");
           }
           lcd.print(secC1);                            // display Seconds
         lcd.setCursor(6,0);                            // Set cursor position on LCD
           if (centC1<10)
           {
           lcd.print("0");
           }
           lcd.print(centC1);                            // Display Hundred
         /*--------------------------display chrono 2 ---------------------------------*/
         lcd.setCursor(14,0);                            // Set cursor position on LCD
         lcd.print(":");
         lcd.setCursor(12,0);                            // Set cursor position on LCD
           if (secC1 <10) 
           {
           lcd.print("00");
           }
           lcd.print(secC1);                            // display Seconds
         lcd.setCursor(15,0);                            // Set cursor position on LCD
           if (centC1<10)
           {
           lcd.print("0");
           }
           lcd.print(centC1);                            // Display Hundred     
      }
centC1 = (tmpPasseChrono1%1000)/10 ;                     //centieme chrono 1 to display
secC1 = (tmpPasseChrono1/1000)%60 ;                      //second chrono 1 to display
centC2 = (tmpPasseChrono1%1000)/10 ;                     //centieme chrono 2 to display
secC2 = (tmpPasseChrono1/1000)%60 ;                      //second chrono 2 to display



/*-------------------------display resultat ---------------------------------------------*/

if (FinVitesse == HIGH && LAP1 == 4 && LAP2 == 4)
  {
   MoyenneChrono = (resultChrono1 + resultChrono2)/2;
   centM = (MoyenneChrono%1000)/10 ;                     //centieme to display
   secM = (MoyenneChrono/1000)%60 ;                      //second to display
   /*--------------------------display Moyenne---------------------------------*/
   lcd.setCursor(5,0);                            // Set cursor position on LCD
   lcd.print(":");
   lcd.setCursor(3,0);                            // Set cursor position on LCD
     if (secM <10) 
       {
       lcd.print("00");
       }
     lcd.print(secM);                            // display Seconds
   lcd.setCursor(6,0);                            // Set cursor position on LCD
     if (centM<10)
       {
       lcd.print("0");
       }
     lcd.print(centM);                            // Display Hundred
  }

/*---------------------------------RAZ---------------------------------------------------*/   

if (StateRAZ == LOW && PrevStateRAZ == HIGH) 
{
  LAP1 = 0;
  LAP2 = 0;
  startChrono1 = 0;    
  startChrono2 = 0;       
  tmpPasseChrono1 = 0;    
  tmpPasseChrono2 = 0;    
  resultChrono1 = 0;      
  resultChrono2 = 0;      
  MoyenneChrono = 0;      
  T1 = 0;                 
  T2 = 0;                 
  BIPBTime = 0;           
  BIPETime = 0;           
  centC1 = 0;             
  secC1=0;                
  centC2 = 0;             
  secC2=0;
  secM=0;
  centM=0;
  FinVitesse = LOW;
  StateA1 = HIGH; 
  StateB1 = HIGH;
  StateA2 = HIGH;
  StateB2 = HIGH;    // status actuel du bouton B2
  StateModeC = HIGH; // status actuel du bouton ModeC
  StateRAZ = HIGH;   // status actuel du bouton RAZ
  StateLarg = HIGH;  // status actuel du bouton Larg
  PrevStateA1 = HIGH;     // status précédént du bouton A1
  PrevStateB1 = HIGH;     // status précédént du bouton B1
  PrevStateA2 = HIGH;     // status précédént du bouton A2
  PrevStateB2 = HIGH;     // status précédént du bouton B2
  PrevStateRAZ = HIGH;    // status précédént du bouton Raz
  PrevStateLarg = HIGH;  
}

/*--------------------------------------------------diplay debug-------------------------------------------*/

    lcd.setCursor(0,1);   
    lcd.print(StateA1);  
    lcd.setCursor(1,1);   
    lcd.print(StateB1);  
    lcd.setCursor(2,1);
    lcd.print(PrevStateA1);
    lcd.setCursor(3,1);
    lcd.print(PrevStateB1);
    lcd.setCursor(4,1);
    lcd.print(PassageAC1);
    lcd.setCursor(5,1);
    lcd.print(PassageBC1);
    lcd.setCursor(6,1);
    lcd.print(LAP1);

}    
    


