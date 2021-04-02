#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#define LED 4

const char* ssid = "wifiname";
const char* password = "xxxxx";
unsigned char status_led=0;
WiFiServer server(80);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  
  Serial.begin(57600);
  Serial.print("testing");
  pinMode(LED, OUTPUT);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client = server.available();
   lcd.begin();
  lcd.backlight();
  if (!client) {
    return;
  }
  
  Serial.println("new client");
  while(!client.available())
  {
    delay(1);
  }
  String req = client.readStringUntil('\r');
  
  int end = 6;
  String t = req.substring(5);

  int x = 0;
  while(t.charAt(x) != ' '){
    x ++;
    Serial.println(x);
  }
  
  Serial.println(req);
  Serial.println(t);
  client.flush();

  if(t=="favicon.ico HTTP/1.1"){
    return;
  }else{
    lcd.print(t.substring(0,x));
  }

  String web = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";

  client.print(web);
}
