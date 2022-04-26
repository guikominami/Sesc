#include <IRremote.h>
#include "DFRobotDFPlayerMini.h"
#include "SoftwareSerial.h"

int RECEIVER_PIN = 12;
int pino_led = 8;
int pino_buzzer = 7;

//---------------------------------------------------------------------------------
//      Áudio
//---------------------------------------------------------------------------------

//Inicia a serial por software nos pinos 10 e 11
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX

DFRobotDFPlayerMini myDFPlayer;

char buf;
int pausa = 0;
int equalizacao = 0;

int resultado = 0;
int selecionada = 0;

//---------------------------------------------------------------------------------

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(pino_led, OUTPUT);
  pinMode(pino_buzzer, OUTPUT);
  
  IrReceiver.begin(RECEIVER_PIN);

  //-------------------------------------------------------
  //  define Audio
  //-------------------------------------------------------
  mySoftwareSerial.begin(9600);
  myDFPlayer.begin(mySoftwareSerial); //inicia módulo MP3, essa linha ficava dentro da Serial
  
  myDFPlayer.setTimeOut(500); //Timeout serial 500ms
  myDFPlayer.volume(30); 
  myDFPlayer.EQ(0); //Equalizacao normal  

  resultado = myDFPlayer.readFileCounts();  
  Serial.println("quantidade áudios"); 
  Serial.println(resultado); 
}

void loop() {
  
   // put your main code here, to run repeatedly:
   if(IrReceiver.decode()){

   Serial.println(IrReceiver.decodedIRData.command);

   switch(IrReceiver.decodedIRData.command){
       case 0x46: 
           Serial.println("UP"); 
           digitalWrite(LED_BUILTIN, HIGH); 
           break;
           
       case 0x15: 
           Serial.println("DOWN"); 
           digitalWrite(LED_BUILTIN, LOW); 
           break;
           
       case 22:  
           Serial.println("Liga Led");
           digitalWrite(pino_led, HIGH);
           break;

       case 25:  
           Serial.println("Desliga Led");
           digitalWrite(pino_led, LOW);
           break;

       case 13:  
           Serial.println("Liga Buzzer");
           tone(pino_buzzer, 523, 300);
           break;

       case 12:  
           Serial.println("Toca áudio");
           myDFPlayer.play(1);
           break;

       case 24:  
           Serial.println("Toca áudio");
           myDFPlayer.play(2);
           break;  
           
       default:   
           Serial.println("Ooops, wrong key!");
           IrReceiver.begin(RECEIVER_PIN);
    }
    delay(1000);
    IrReceiver.resume();
  }
}
