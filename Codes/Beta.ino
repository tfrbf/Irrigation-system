#include <ESP32Servo.h>

#define sensor1 12
#define sensor2 13
#define sensor3 14
#define servo 5
#define pump 4
#define LED 2

Servo s1;  //initialize servo motor

unsigned int sensor_value1 = 0;
unsigned int sensor_value2 = 0;
unsigned int sensor_value3 = 0;

// Set how much pump should be active in seconde
const byte pump_time = 2;


void setup() {
  Serial.begin(9600);
  pinMode(sensor1, INPUT);  //Soilmoisture 1
  pinMode(sensor2, INPUT);  //Soilmoisture 2
  pinMode(sensor3, INPUT);  //Soilmoisture 3
  pinMode(pump, OUTPUT);    //Pump
  pinMode(LED, OUTPUT);
  pinMode(servo, OUTPUT);  // Servo
  s1.attach(servo);

  digitalWrite(pump, HIGH);  //Set pump in off mode
}

void loop() {
  // Getting sensors data
  sensor_value1 = analogRead(sensor1);
  sensor_value2 = analogRead(sensor2);
  sensor_value3 = analogRead(sensor3);

  delay(10);

  Serial.print("Sensor1: ");
  Serial.print(sensor_value1);
  Serial.print("\t");
  Serial.print("Sensor2: ");
  Serial.print(sensor_value2);
  Serial.print("\t");
  Serial.print("Sensor3: ");
  Serial.print(sensor_value3);
  Serial.print("\n");

  if (sensor_value1 > 300) {
    s1.write(0);
    s1.write(180);
    pump_activate();
    s1.write(0);

  } else digitalWrite(sensor1, LOW);

  if (sensor_value2 > 300) {
    s1.write(0);
    s1.write(90);
    pump_activate();
    s1.write(0);

  } else digitalWrite(sensor2, LOW);

  if (sensor_value3 > 300) {
    s1.write(0);
    s1.write(0);
    pump_activate();
    s1.write(0);

  } else digitalWrite(sensor3, LOW);

  delay(500);  // Delay a little bit to improve simulation performance
}

void pump_activate() {
  
  digitalWrite(LED, HIGH);
  digitalWrite(pump, HIGH);
  delay(pump_time * 1000);
  digitalWrite(LED, LOW);
  digitalWrite(pump, LOW);
}
