#include "LedControl.h"
#include "binary.h"
 
/*
 * Conectar os pinos da Matriz de Led 8x8 no Arduino
 * DIN conecta ao pino 7
 * CLK conecta ao pino 9
 * CS conecta ao pino 8 
 * 
 * Conectar botão no pino 5 - usar resistor 10k no GND
 * Conectar buzzer - pino positivo na porta 12 e negativo no GND
*/

//LedControl lc=LedControl(DIN,CLK,CS,1); //1 max7219 
LedControl lc=LedControl(7,9,8,1); //1 max7219

int sensor_presenca1 = 6;
int sensor_presenca2 = 5;
int resultado = 0;
int direita = 0;
int esquerda = 0;

// Definimos padrões binários para cada número do dado (1 a 6)
byte fechado[] = {
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000};

byte olho1_meio[] = {
B00000000,
B00000000,
B00011000,
B00111100,
B00111100,
B00011000,
B00000000,
B00000000};

byte olho1_pisca1[] = {
B00000000,
B00000000,
B00010000,
B00111000,
B00111000,
B00010000,
B00000000,
B00000000};

byte olho1_pisca2[] = {
B00000000,
B00000000,
B00010000,
B00110000,
B00010000,
B00000000,
B00000000,
B00000000};

byte olho1_esquerda1[] = {
B00000000,
B00011000,
B00111100,
B00111100,
B00011000,
B00000000,
B00000000,
B00000000};

byte olho1_esquerda2[] = {
B00011000,
B00111100,
B00111100,
B00011000,
B00000000,
B00000000,
B00000000,
B00000000};

byte olho1_direita1[] = {
B00000000,
B00000000,
B00000000,
B00011000,
B00111100,
B00111100,
B00011000,
B00000000};

byte olho1_direita2[] = {
B00000000,
B00000000,
B00000000,
B00000000,
B00011000,
B00111100,
B00111100,
B00011000};

byte olho2_meio[] = {
B00000000,
B00000000,
B00011000,
B00111100,
B00111100,
B00011000,
B00000000,
B00000000};

byte olho2_pisca1[] = {
B00000000,
B00000000,
B00010000,
B00111000,
B00111000,
B00010000,
B00000000,
B00000000};

byte olho2_pisca2[] = {
B00000000,
B00000000,
B00010000,
B00110000,
B00110000,
B00000000,
B00000000,
B00000000};

byte olho2_direita1[] = {
B00000000,
B00000000,
B00000000,
B00011000,
B00111100,
B00111100,
B00011000,
B00000000};

byte olho2_direita2[] = {
B00000000,
B00000000,
B00000000,
B00000000,
B00011000,
B00111100,
B00111100,
B00011000};

byte olho2_esquerda1[] = {
B00000000,
B00011000,
B00111100,
B00111100,
B00011000,
B00000000,
B00000000,
B00000000};

byte olho2_esquerda2[] = {
B00011000,
B00111100,
B00111100,
B00011000,
B00000000,
B00000000,
B00000000,
B00000000};

void setup() {
  
  lc.shutdown(0,false);
    
  // Ajustamos o brilho da matriz de leds para um valor médio
  lc.setIntensity(0,7);
    
  // Limpamos o display
  lc.clearDisplay(0); 

  pinMode(sensor_presenca1, INPUT);
  pinMode(sensor_presenca2, INPUT);

  Serial.begin(9600);
}
 
void loop() {

  int valor_sensor_presenca1 = digitalRead(sensor_presenca1);
  int valor_sensor_presenca2 = digitalRead(sensor_presenca2);

  Serial.println("valor_sensor_presenca1");
  Serial.println(valor_sensor_presenca1);

  Serial.println("valor_sensor_presenca2");
  Serial.println(valor_sensor_presenca2);    

  if (valor_sensor_presenca1 == 1 && valor_sensor_presenca2 == 1){
      piscaOlhos();
  }
  
  else if (valor_sensor_presenca2 == 0){
      viraOlhosDireita();
  }

  else if (valor_sensor_presenca1 == 0){
      viraOlhosEsquerda();
  }

  delay(50);  
}
 
void piscaOlhos(){

    direita = 0;

    mostraResultado("olho1_meio", lc);
    delay(2000);         
    mostraResultado("olho1_pisca1", lc); 
    delay(50);       
    mostraResultado("olho1_pisca2", lc); 
    delay(50);    
    mostraResultado("fechado", lc); 
    delay(50);    
    mostraResultado("olho1_pisca2", lc); 
    delay(50); 
    mostraResultado("olho1_pisca1", lc);     
    delay(50);              
  
}

void viraOlhosDireita(){

    if (direita == 0){
      mostraResultado("olho1_direita1", lc);
      delay(100);
    }
    
    mostraResultado("olho1_direita2", lc);
    delay(1000);

    direita = 1;
    
}

void viraOlhosEsquerda(){

    if (esquerda == 0){
      mostraResultado("olho1_esquerda1", lc);
      delay(100);
    }
    
    mostraResultado("olho1_esquerda2", lc);
    delay(1000);

    esquerda = 1;
    
}
 
void mostraResultado(int resultado, LedControl led_control){
  if(resultado=="olho1_meio"){
    led_control.setRow(0,0,olho1_meio[0]);
    led_control.setRow(0,1,olho1_meio[1]);
    led_control.setRow(0,2,olho1_meio[2]);
    led_control.setRow(0,3,olho1_meio[3]);
    led_control.setRow(0,4,olho1_meio[4]);
    led_control.setRow(0,5,olho1_meio[5]);
    led_control.setRow(0,6,olho1_meio[6]);
    led_control.setRow(0,7,olho1_meio[7]);
  }
  else if(resultado=="olho2_meio"){
    led_control.setRow(0,0,olho2_meio[0]);
    led_control.setRow(0,1,olho2_meio[1]);
    led_control.setRow(0,2,olho2_meio[2]);
    led_control.setRow(0,3,olho2_meio[3]);
    led_control.setRow(0,4,olho2_meio[4]);
    led_control.setRow(0,5,olho2_meio[5]);
    led_control.setRow(0,6,olho2_meio[6]);
    led_control.setRow(0,7,olho2_meio[7]);
  }
  else if(resultado=="olho1_direita1"){
    led_control.setRow(0,0,olho1_direita1[0]);
    led_control.setRow(0,1,olho1_direita1[1]);
    led_control.setRow(0,2,olho1_direita1[2]);
    led_control.setRow(0,3,olho1_direita1[3]);
    led_control.setRow(0,4,olho1_direita1[4]);
    led_control.setRow(0,5,olho1_direita1[5]);
    led_control.setRow(0,6,olho1_direita1[6]);
    led_control.setRow(0,7,olho1_direita1[7]);
  }
  else if(resultado=="olho1_direita2"){
    led_control.setRow(0,0,olho1_direita2[0]);
    led_control.setRow(0,1,olho1_direita2[1]);
    led_control.setRow(0,2,olho1_direita2[2]);
    led_control.setRow(0,3,olho1_direita2[3]);
    led_control.setRow(0,4,olho1_direita2[4]);
    led_control.setRow(0,5,olho1_direita2[5]);
    led_control.setRow(0,6,olho1_direita2[6]);
    led_control.setRow(0,7,olho1_direita2[7]);
  }
  else if(resultado=="olho2_direita1"){
    led_control.setRow(0,0,olho2_direita1[0]);
    led_control.setRow(0,1,olho2_direita1[1]);
    led_control.setRow(0,2,olho2_direita1[2]);
    led_control.setRow(0,3,olho2_direita1[3]);
    led_control.setRow(0,4,olho2_direita1[4]);
    led_control.setRow(0,5,olho2_direita1[5]);
    led_control.setRow(0,6,olho2_direita1[6]);
    led_control.setRow(0,7,olho2_direita1[7]);
  }
  else if(resultado=="olho2_direita2"){
    led_control.setRow(0,0,olho2_direita2[0]);
    led_control.setRow(0,1,olho2_direita2[1]);
    led_control.setRow(0,2,olho2_direita2[2]);
    led_control.setRow(0,3,olho2_direita2[3]);
    led_control.setRow(0,4,olho2_direita2[4]);
    led_control.setRow(0,5,olho2_direita2[5]);
    led_control.setRow(0,6,olho2_direita2[6]);
    led_control.setRow(0,7,olho2_direita2[7]);
  }
  else if(resultado=="olho1_esquerda1"){
    led_control.setRow(0,0,olho1_esquerda1[0]);
    led_control.setRow(0,1,olho1_esquerda1[1]);
    led_control.setRow(0,2,olho1_esquerda1[2]);
    led_control.setRow(0,3,olho1_esquerda1[3]);
    led_control.setRow(0,4,olho1_esquerda1[4]);
    led_control.setRow(0,5,olho1_esquerda1[5]);
    led_control.setRow(0,6,olho1_esquerda1[6]);
    led_control.setRow(0,7,olho1_esquerda1[7]);
  }
  else if(resultado=="olho1_esquerda2"){
    led_control.setRow(0,0,olho1_esquerda2[0]);
    led_control.setRow(0,1,olho1_esquerda2[1]);
    led_control.setRow(0,2,olho1_esquerda2[2]);
    led_control.setRow(0,3,olho1_esquerda2[3]);
    led_control.setRow(0,4,olho1_esquerda2[4]);
    led_control.setRow(0,5,olho1_esquerda2[5]);
    led_control.setRow(0,6,olho1_esquerda2[6]);
    led_control.setRow(0,7,olho1_esquerda2[7]);
  }
  else if(resultado=="olho2_esquerda1"){
    led_control.setRow(0,0,olho2_esquerda1[0]);
    led_control.setRow(0,1,olho2_esquerda1[1]);
    led_control.setRow(0,2,olho2_esquerda1[2]);
    led_control.setRow(0,3,olho2_esquerda1[3]);
    led_control.setRow(0,4,olho2_esquerda1[4]);
    led_control.setRow(0,5,olho2_esquerda1[5]);
    led_control.setRow(0,6,olho2_esquerda1[6]);
    led_control.setRow(0,7,olho2_esquerda1[7]);
  }
  else if(resultado=="olho2_esquerda2"){
    led_control.setRow(0,0,olho2_esquerda2[0]);
    led_control.setRow(0,1,olho2_esquerda2[1]);
    led_control.setRow(0,2,olho2_esquerda2[2]);
    led_control.setRow(0,3,olho2_esquerda2[3]);
    led_control.setRow(0,4,olho2_esquerda2[4]);
    led_control.setRow(0,5,olho2_esquerda2[5]);
    led_control.setRow(0,6,olho2_esquerda2[6]);
    led_control.setRow(0,7,olho2_esquerda2[7]);
  }        
  else if(resultado=="olho1_pisca1"){
    led_control.setRow(0,0,olho1_pisca1[0]);
    led_control.setRow(0,1,olho1_pisca1[1]);
    led_control.setRow(0,2,olho1_pisca1[2]);
    led_control.setRow(0,3,olho1_pisca1[3]);
    led_control.setRow(0,4,olho1_pisca1[4]);
    led_control.setRow(0,5,olho1_pisca1[5]);
    led_control.setRow(0,6,olho1_pisca1[6]);
    led_control.setRow(0,7,olho1_pisca1[7]);
  }
  else if(resultado=="olho1_pisca2"){
    led_control.setRow(0,0,olho1_pisca2[0]);
    led_control.setRow(0,1,olho1_pisca2[1]);
    led_control.setRow(0,2,olho1_pisca2[2]);
    led_control.setRow(0,3,olho1_pisca2[3]);
    led_control.setRow(0,4,olho1_pisca2[4]);
    led_control.setRow(0,5,olho1_pisca2[5]);
    led_control.setRow(0,6,olho1_pisca2[6]);
    led_control.setRow(0,7,olho1_pisca2[7]);
  }
  else if(resultado=="fechado"){
    led_control.setRow(0,0,fechado[0]);
    led_control.setRow(0,1,fechado[1]);
    led_control.setRow(0,2,fechado[2]);
    led_control.setRow(0,3,fechado[3]);
    led_control.setRow(0,4,fechado[4]);
    led_control.setRow(0,5,fechado[5]);
    led_control.setRow(0,6,fechado[6]);
    led_control.setRow(0,7,fechado[7]);
  }
  else if(resultado=="olho2_pisca1"){
    led_control.setRow(0,0,olho2_pisca1[0]);
    led_control.setRow(0,1,olho2_pisca1[1]);
    led_control.setRow(0,2,olho2_pisca1[2]);
    led_control.setRow(0,3,olho2_pisca1[3]);
    led_control.setRow(0,4,olho2_pisca1[4]);
    led_control.setRow(0,5,olho2_pisca1[5]);
    led_control.setRow(0,6,olho2_pisca1[6]);
    led_control.setRow(0,7,olho2_pisca1[7]);
  }
  else if(resultado=="olho2_pisca2"){
    led_control.setRow(0,0,olho2_pisca2[0]);
    led_control.setRow(0,1,olho2_pisca2[1]);
    led_control.setRow(0,2,olho2_pisca2[2]);
    led_control.setRow(0,3,olho2_pisca2[3]);
    led_control.setRow(0,4,olho2_pisca2[4]);
    led_control.setRow(0,5,olho2_pisca2[5]);
    led_control.setRow(0,6,olho2_pisca2[6]);
    led_control.setRow(0,7,olho2_pisca2[7]);
  }
}
