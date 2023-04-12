#include <ESP32Servo.h>
Servo s1;

unsigned int soilmoisture1 = 0;
//unsigned int soilmoisture1 = 0;
//unsigned int soilmoisture1 = 0;

// Set how much pump should be active in seconde
byte pump_time = 2;


void setup() {
  Serial.begin(9600);
  pinMode(13, INPUT);  //Soilmoisture 1
  //pinMode( , INPUT); //Soilmoisture 2
  //pinMode( , INPUT); //Soilmoisture 3
  pinMode(12, OUTPUT);  // Servo
  s1.attach(12);
  pinMode(14, OUTPUT);     //Pump
  //pinMode(uint8_t pin, OUTPUT); 
  digitalWrite(14, HIGH);  //Set pump in off mode
}

void loop() {
  // Getting sensors data
  soilmoisture1 = analogRead(13);
  //soilmoisture2 = analogRead();
  //soilmoisture3 = analogRead();
  Serial.print("Humidity: ");
  Serial.print(soilmoisture1);
  //Serial.println(soilmoisture2);
  //Serial.println(soilmoisture3);

  if (soilmoisture1 > 200) {
    s1.write(0);
    s1.write(180);
    pump_activate();
    s1.write(0);

  } else digitalWrite(12, LOW);

  // if (soilmoisture2 > 200) {
  //   s1.write(0);
  //   s1.write(90);
  //   pump_activate();
  //   s1.write(0);

  // } else digitalWrite(12, LOW);

  // if (soilmoisture3 > 200) {
  //   s1.write(0);
  //   s1.write(0);
  //   pump_activate();
  //   s1.write(0);

  // } else digitalWrite(12, LOW);

  delay(10);  // Delay a little bit to improve simulation performance
}

void pump_activate()
{
  digitalWrite(14, LOW);
  delay(pump_time * 1000);
  digitalWrite(14, HIGH);
}
