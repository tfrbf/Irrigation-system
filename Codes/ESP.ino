

int soilmoisture1 = 0;
int soilmoisture2 = 0;
int soilmoisture3 = 0;



void setup()
{
  //pinMode(A0, INPUT);
  //pinMode(A1, INPUT);
  //pinMode(A2, INPUT);
  //s1.attach(9);
  pinMode(34,INPUT);
  Serial.begin(9600);
  pinMode(9, OUTPUT);
}


void loop()
{
  soilmoisture1 = analogRead(34);

  Serial.println(soilmoisture1);
  delay(1000);
  
}

