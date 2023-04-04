#include <Servo.h>
Servo s1;
unsigned int plots[] = { 12, 13, 14 };
int i;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(12, INPUT);
  pinMode(13, INPUT);
  pinMode(14, INPUT);
  s1.attach(2);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i <= 2; i++) {
    Serial.print("Plot: ");
    Serial.print(i + 1);
    Serial.print(" = ");
    Serial.print(analogRead(plots[i]));
  }

  for (int i = 0; i <= 2; i++) {
    if (analogRead(plots[i]))
      popm_active(i);
  }
}

void popm_active(int i) {
  Serial.print("Turning to ");
  Serial.print(i + 1);
  s1.write(i * 90);
}
