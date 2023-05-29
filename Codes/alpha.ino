// Libraries
#include <Servo.h>

// Define variabels
#define soil1 A0
#define soil2 A1
#define soil3 A2
#define servo 3
#define pump 5


// Global variabels
unsigned int soil_value1 = 0;
unsigned int soil_value2 = 0;
unsigned int soil_value3 = 0;
const byte pump_time = 2;

Servo s1;

void setup() {
  Serial.begin(9600);
  
  pinMode(pump, OUTPUT);   
  pinMode(servo, OUTPUT);  
  s1.attach(servo);
  digitalWrite(pump, HIGH);
}


void loop() {
  
  // Getting sensors data
  soil_value1 = analogRead(soil1);
  soil_value2 = analogRead(soil2);
  soil_value3 = analogRead(soil3);

  // Printing Values
  
  Serial.print("soil1: ");
  Serial.print(soil_value1);
  Serial.print("  ");
  Serial.print("soil2: ");
  Serial.print(soil_value2);
  Serial.print("  ");
  Serial.print("soil3: ");
  Serial.print(soil_value3);
  Serial.print("\n");
  
  if ((soil_value1 > 300)) {
    s1.write(0);
    s1.write(0);
    delay(100);
    pump_activate();
    s1.write(0);
  } else digitalWrite(soil1, LOW);

  if ((soil_value2 > 300)) {
    s1.write(0);
    s1.write(90);
    delay(100);
    pump_activate();
    s1.write(0);

  } else digitalWrite(soil2, LOW);

  if (soil_value3 > 300)  {
    s1.write(0);
    s1.write(180);
    delay(100);
    pump_activate();
    s1.write(0);

  } else digitalWrite(soil3, LOW);
  
  delay(100);
}

void pump_activate() {

  digitalWrite(pump, LOW);
  delay(pump_time * 1000);
  digitalWrite(pump, HIGH);
}
