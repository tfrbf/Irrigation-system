#include <Servo.h>
#include <Keypad.h>

#define sensor1 A0
#define sensor2 A1
#define sensor3 A2
#define servo 3
#define pump 4
#define LED 5
#define mq5 A3
#define ldr A4
 

Servo s1;  //initialize servo motor

const byte rows = 4;
const byte clos = 3;
char keys [rows][clos] = {
  '1','2','3',
  '4','5','6',
  '7','8','9',
  '*','0','#'
};

byte rowPins[rows] = {7,8,9,10};
byte colPins[clos] = {11,12,13};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, clos );

unsigned int sensor_value1 = 0;
unsigned int sensor_value2 = 0;
unsigned int sensor_value3 = 0;
unsigned int mq5_value = 0;
unsigned int ldr_value;

// Set how much pump should be active in seconde
const byte pump_time = 2;


void setup() {
  Serial.begin(9600);
  pinMode(sensor1, INPUT);  //Soilmoisture 1
  pinMode(sensor2, INPUT);  //Soilmoisture 2
  pinMode(sensor3, INPUT);  //Soilmoisture 3
  pinMode(pump, OUTPUT);    //Pump
  digitalWrite(pump, HIGH); // set pump off mode
  pinMode(LED, OUTPUT);
  pinMode(servo, OUTPUT);  // Servo
  s1.attach(servo);
    


  digitalWrite(pump, LOW);  //Set pump in off mode
}

void loop() {
  char key = keypad.getKey();
  if (key){
    Serial.print("Key Pressed : ");
    Serial.println(key);
  }
  // Getting sensors data
  sensor_value1 = analogRead(sensor1);
  sensor_value2 = analogRead(sensor2);
  sensor_value3 = analogRead(sensor3);
  mq5_value = analogRead(mq5);
  ldr_value = analogRead(ldr);

  delay(10);

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
  Serial.print(mq5);
  Serial.print("\t");
  Serial.print("Light: ");
  Serial.print(ldr_value);
  Serial.print("\n");

  if ((sensor_value1 > 300) || (key == '1')) {
    s1.write(0);
    s1.write(180);
    pump_activate();
    s1.write(0);

  } else digitalWrite(sensor1, LOW);

  if ((sensor_value2 > 300) || (key == '2')) {
    s1.write(0);
    s1.write(90);
    pump_activate();
    s1.write(0);

  } else digitalWrite(sensor2, LOW);

  if ((sensor_value3 > 300) || (key == '3')) {
    s1.write(0);
    s1.write(0);
    pump_activate();
    s1.write(0);

  } else digitalWrite(sensor3, LOW);

  delay(1000);  // Delay a little bit to improve simulation performance
}

void pump_activate() {
  
  digitalWrite(LED, HIGH);
  digitalWrite(pump, LOW);
  delay(pump_time * 1000);
  digitalWrite(LED, LOW);
  digitalWrite(pump, HIGH);
}
