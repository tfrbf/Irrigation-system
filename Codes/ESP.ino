
#include<ESP32Servo.h>
Servo s1;

int soilmoisture1 = 0;

int count=0;


void setup()
{
  pinMode(13, INPUT);
 pinMode(12, OUTPUT);
  s1.attach(12);
  Serial.begin(9600);
  
}


void loop()
{
  soilmoisture1 = analogRead(13);
 // soilmoisture2 = analogRead(A1);
 // soilmoisture3 = analogRead(A2);
  Serial.println(soilmoisture1);
 // Serial.println(soilmoisture2);
 // Serial.println(soilmoisture3);
  
  if (soilmoisture1 >200) {
    
    
    s1.write(0);
    delay(1000);
    s1.write(180);
    delay(1000);
    s1.write(0);

  } else {
    digitalWrite(9, LOW);
  }
  
  
  delay(10); // Delay a little bit to improve simulation performance
}
