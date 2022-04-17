// GROUP 5
// CPE 301.1001
// Semester Project

#include <dht.h>
#include <LiquidCrystal.h>

#include <string.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

dht DHT;

// LCD
#define DHT11_PIN 7

// MOTOR
#define ENABLE 44
#define DIRA 45
#define DIRB 46

// WATER LEVEL SENSOR
int resval = 0;  // holds the value
int respin = A5; // sensor pin used

void setup(){
  lcd.begin(16, 2);
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
  
  Serial.begin(9600);
}

void loop(){
  // MOTOR
  digitalWrite(DIRA,HIGH); //one way
  digitalWrite(DIRB,LOW);
  analogWrite(ENABLE,100); //enable on
  //delay(200);
  
  // LCD / TEMP / HUMIDITY
  int chk = DHT.read11(DHT11_PIN);
  lcd.setCursor(0,0); 
  lcd.print("Temp: ");
  lcd.print(DHT.temperature);
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.print(DHT.humidity);
  lcd.print("%");

  // WATER LEVEL SENSOR
  /* The resistance value is inversely proportional to the water level.
  As a result, the resistance value should be divided by 1000, since the max value is ~1024. */
  resval = analogRead(respin);
  resval = resval / 1000;
  Serial.print(resval);
  if (resval<=100){
    Serial.println("Water Level: Empty"); 
  } 
  else if (resval>100 && resval<=300){ 
    Serial.println("Water Level: Low"); 
  } 
  else if (resval>300 && resval<=330){ 
    Serial.println("Water Level: Medium");
  } 
  else if (resval>330){ 
    Serial.println("Water Level: High"); 
  }

  delay(5000);

  // MOTOR (FROM EXAMPLE)
  //---PWM example, full speed then slow
 /*
  for (int i=255;i>100;i--) {
  digitalWrite(DIRA,HIGH); //one way
  digitalWrite(DIRB,LOW);
  analogWrite(ENABLE,i); //enable on
  delay(200);
  }
  for (int i=100;i<255;i++) {
  digitalWrite(DIRA,HIGH); //one way
  digitalWrite(DIRB,LOW);
  analogWrite(ENABLE,i); //enable on
  delay(200);  
  } */
}
