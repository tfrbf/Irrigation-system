#include <Servo.h>
#include <Keypad.h>

#define sensor1 A0
#define sensor2 A1
#define sensor3 A2
#define mq5 A3
#define ldr A4
#define temp A5
#define servo 3
#define pump 4
#define buzzer 2
char blth;
String voice;


Servo s1;  //initialize servo motor

const byte rows = 4;
const byte clos = 3;
char keys[rows][clos] = {
  '1', '2', '3',
  '4', '5', '6',
  '7', '8', '9',
  '*', '0', '#'
};

byte rowPins[rows] = { 7, 8, 9, 10 };
byte colPins[clos] = { 11, 12, 13 };
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, clos);

unsigned int sensor_value1 = 0;
unsigned int sensor_value2 = 0;
unsigned int sensor_value3 = 0;
unsigned int mq5_value = 0;
unsigned int ldr_value;
unsigned int led_value = 0;
int temp_value = 0;

// Set how much pump should be active in seconde
const byte pump_time = 3;


void setup() {
  Serial.begin(9600);
  pinMode(sensor1, INPUT);  //Soilmoisture 1
  pinMode(sensor2, INPUT);  //Soilmoisture 2
  pinMode(sensor3, INPUT);  //Soilmoisture 3
  pinMode(pump, OUTPUT);    //Pump
  pinMode(servo, OUTPUT);   // Servo
  pinMode(buzzer, OUTPUT);
  s1.attach(servo);
  digitalWrite(pump, HIGH);
  if (Serial.available() > 0)
    Serial.print("\tBluetooth Connected Seccessfully.\a");
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    Serial.print("Key Pressed : ");
    Serial.println(key);
  }

  // Getting sensors data
  sensor_value1 = analogRead(sensor1);
  sensor_value2 = analogRead(sensor2);
  sensor_value3 = analogRead(sensor3);
  mq5_value = analogRead(mq5);
  ldr_value = analogRead(ldr);
  temp_value = analogRead(temp);

  delay(10);

  // Printing Values
  Serial.print("Sensor1: ");
  Serial.print(sensor_value1);
  Serial.print("\t");
  Serial.print("Sensor2: ");
  Serial.print(sensor_value2);
  Serial.print("\t");
  Serial.print("Sensor3: ");
  Serial.print(sensor_value3);
  Serial.print("\t");
  Serial.print("MQ5: ");
  Serial.print(mq5_value);
  Serial.print("\t");
  Serial.print("Light: ");
  Serial.print(ldr_value);
  Serial.print("\t");
  Serial.print("temp: ");
  Serial.print(temp_value);
  Serial.print("\n");


  //LED   
  led_value = map(ldr_value, 0, 1024, 0, 100); 
    delay(500);
    pump_activate();
    s1.write(0);
    voice = "";

  } else digitalWrite(sensor1, LOW);

  if ((sensor_value2 > 300) || (key == '5') || (voice == "left") || (voice == "lift") || (voice == "5")) {
    s1.write(0);
    s1.write(90);
    delay(500);
    pump_activate();
    s1.write(0);
    voice = "";

  } else digitalWrite(sensor2, LOW);

  if ((sensor_value3 > 300) || (key == '3') || (voice == "up") || voice == "3") {
    s1.write(0);
    s1.write(0);
    delay(500);
    pump_activate();
    s1.write(0);
    voice = "";

  } else digitalWrite(sensor3, LOW);

  delay(1000);
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
