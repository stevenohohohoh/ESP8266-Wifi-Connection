#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
char auth[] = "AogSsrFOBhYackLXGc-sd67V3oY_Dofc";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "IODATA-e9742c-2G";
char pass[] = "5261564395227";

int In1 = 0; //D3
int In2 = 2; //D4
int ENA = 4; //D2

int In3 = 13; //D7
int In4 = 12; //D6
int ENAB = 14; //D5

boolean state = true;

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(In1,OUTPUT);
  pinMode(In2,OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(In3,OUTPUT);
  pinMode(In4,OUTPUT);
  pinMode(ENAB, OUTPUT);
  Blynk.begin(auth, ssid, pass);
}
BLYNK_WRITE(V0)
{
  int pinData = param.asInt(); 
  if (pinData == 1){
    digitalWrite(ENA, LOW);
    digitalWrite(In1,HIGH);
    digitalWrite(In2, LOW);
    digitalWrite(ENA, HIGH);
  }else{
    digitalWrite(ENA, LOW);
  }
}

BLYNK_WRITE(V1)//back
{
  int pinData = param.asInt(); 
  if (pinData == 1){
  digitalWrite(ENA, LOW);
  digitalWrite(In1,LOW);
  digitalWrite(In2, HIGH);
  digitalWrite(ENA, HIGH);
  }else{
   digitalWrite(ENA, LOW);
  }
}

BLYNK_WRITE(V2){
  int pinData = param.asInt(); 
  if (pinData == 1){
    digitalWrite(ENAB, LOW);
   digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
   digitalWrite(ENAB, HIGH);
  }else{
    digitalWrite(ENAB, LOW);
  }
}

BLYNK_WRITE(V3){
  int pinData = param.asInt(); 
  if (pinData == 1){
  digitalWrite(ENAB, LOW);
   digitalWrite(In3, HIGH);
    digitalWrite(In4, LOW);
    digitalWrite(ENAB, HIGH);
  }else{
    digitalWrite(ENAB, LOW);
  }
}

BLYNK_WRITE(V4){
  digitalWrite(ENAB, LOW);
  digitalWrite(ENA, LOW);
}
BLYNK_WRITE(V5){
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  digitalWrite(ENAB, HIGH);
  digitalWrite(ENA, HIGH);
  delay(2000);
  digitalWrite(ENAB, LOW);  
  digitalWrite(ENAB, LOW);
  
}
void loop()
{
  Blynk.run();
}
