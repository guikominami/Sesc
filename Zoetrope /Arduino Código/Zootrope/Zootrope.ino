
//5V DO DRIVER DE MOTOR LIGADO NO VIN DO ARDUINO, PARA LIGAR UM FONTE EXTERNA
//GND DO DRIVER DE MOTOR LIGADO NO GND DO ARDUINO

//INI3 LIGADO NO 10 DO ARDUINO
//INI4 LIGADO NO 11 DO ARDUINO

int IN3 = 10;
int IN4 = 11;

int pinLed1 = 2;
int pinLed2 = 5;

int state;
int flag = 0;

int ENB = 3;

void setup() {

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(pinLed1, OUTPUT);  
  pinMode(pinLed2, OUTPUT);  

  Serial.begin(9600);
}

void loop() {

  //Caso necessário testar os motores
  rodaMotor();
  
}

void rodaMotor()
{
  //MOTOR 2
  analogWrite(ENB, 50);  //Motor com rotação máxima (0-255)
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  digitalWrite(pinLed1, HIGH);
  digitalWrite(pinLed2, HIGH);
  
  delay(50);
  
  digitalWrite(pinLed1, LOW);
  digitalWrite(pinLed2, LOW);  

  delay(50);  
}

void paraMotor()
{
  //MOTOR 2
  //analogWrite(ENB, 1000);  //Motor com rotação máxima (0-255)
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
