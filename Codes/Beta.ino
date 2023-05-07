// Libraries
#include <Servo.h>
#include <Keypad.h>
#include "SRF05.h"

// Define variabels
#define soil1 A0
#define soil2 A1
#define soil3 A2
#define mq5 A3
#define ldr A4
#define servo 3
#define pump 5
#define buzzer 2


// Global variabels
float dis = 0;
unsigned int soil_value1 = 0;
unsigned int soil_value2 = 0;
unsigned int soil_value3 = 0;
unsigned int mq5_value = 0;
unsigned int ldr_value;
unsigned int led_value = 0;
const byte pump_time = 3;
const int trigger = 11;
const int echo = 10;
char blth = "N";
char key = "N" ;
String voice;

SRF05 SRF(trigger, echo);
Servo s1;

// Keyboard
const byte rows = 2;
const byte clos = 3;
char keys[rows][clos] = {
  '1', '2', '3',
  '4', '5', '6'
};
byte rowPins[rows] = { 9, 7 };
byte colPins[clos] = { 8, 12, 13 };
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, clos);
// End keyboard

void setup() {
  Serial.begin(115200);
  Serial.println(__FILE__);
  SRF.setCorrectionFactor(1.035);
  pinMode(soil1, INPUT);  //Soilmoisture 1
  pinMode(soil2, INPUT);  //Soilmoisture 2
  pinMode(soil3, INPUT);  //Soilmoisture 3
  pinMode(pump, OUTPUT);   
  pinMode(servo, OUTPUT);  
  pinMode(buzzer, OUTPUT);
  s1.attach(servo);
  digitalWrite(pump, HIGH);
}

void loop() {
  key = keypad.getKey();

  // Getting sensors data
  soil_value1 = analogRead(soil1);
  soil_value2 = analogRead(soil2);
  soil_value3 = analogRead(soil3);
  mq5_value = analogRead(mq5);
  ldr_value = analogRead(ldr);
  dis = SRF.getCentimeter();

  // Printing Values
  Serial.print("Key: ");
  Serial.print(key);
  Serial.print("\t");
  Serial.print("distance: ");
  Serial.print(dis);
  Serial.print("\t");
  Serial.print("soil1: ");
  Serial.print(soil_value1);
  Serial.print("\t");
  Serial.print("soil2: ");
  Serial.print(soil_value2);
  Serial.print("\t");
  Serial.print("soil3: ");
  Serial.print(soil_value3);
  Serial.print("\t");
  Serial.print("MQ5: ");
  Serial.print(mq5_value);
  Serial.print("\t");
  Serial.print("Light: ");
  Serial.print(ldr_value);
  Serial.print("\n");

  //LED
  //digitalWrite(LED,led_value = map(ldr_value, 0, 1024, 0, 100));
  
  if ((soil_value1 > 300) || (key == '1') || (voice == "right") || (voice == "1")) {
    s1.write(0);
    s1.write(0);
    delay(500);
    pump_activate();
    s1.write(0);
    voice = "";
  } else digitalWrite(soil1, LOW);

  if ((soil_value2 > 300) || (key == '5') || (voice == "left") || (voice == "lift") || (voice == "5")) {
    s1.write(0);
    s1.write(90);
    delay(500);
    pump_activate();
    s1.write(0);
    voice = "";

  } else digitalWrite(soil2, LOW);

  if ((soil_value3 > 300) || (key == '3') || (voice == "up") || voice == "3") {
    s1.write(0);
    s1.write(180);
    delay(500);
    pump_activate();
    s1.write(0);
    voice = "";

  } else digitalWrite(soil3, LOW);

  if (Serial.available() > 0) {
    voice = "";
    delay(2);
    voice = Serial.readString();
    delay(2);
    Serial.println(voice);
  }
}

void pump_activate() {

  digitalWrite(pump, LOW);
  delay(pump_time * 1000);
  digitalWrite(pump, HIGH);
}
