
#include<Servo.h>
Servo s1;

int soilmoisture1 = 0;
int soilmoisture2 = 0;
int soilmoisture3 = 0;
int count=0;


void setup()
{
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  s1.attach(9);
  Serial.begin(9600);
  pinMode(9, OUTPUT);
}


void loop()
{
  soilmoisture1 = analogRead(A0);
  soilmoisture2 = analogRead(A1);
  soilmoisture3 = analogRead(A2);
  Serial.println(soilmoisture1);
  Serial.println(soilmoisture2);
  Serial.println(soilmoisture3);
  
  if (soilmoisture1 <= 200) {
    for(count = 0;count <=3;count++)
    {
     s1.write(0);
    delay(1000);
    s1.write(180);
    delay(1000);
    s1.write(0);
    }
  } else {
    digitalWrite(9, LOW);
  }
  
  
    if (soilmoisture2 <= 200) {
    s1.write(0);
    delay(1000);
    s1.write(90);
    delay(1000);
    s1.write(0);
  } else {
    digitalWrite(9, LOW);
  }
  
  
  
    if (soilmoisture3 <= 200) {
    s1.write(0);
    delay(1000);
  } else {
    digitalWrite(9, LOW);
  }
  
  
  delay(10); // Delay a little bit to improve simulation performance
}
