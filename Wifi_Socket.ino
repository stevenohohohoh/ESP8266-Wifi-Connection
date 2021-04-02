#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define NAME "IODATA-e9742c-2G"
#define PASS "5261564395227"

const char* host = "localhost";
LiquidCrystal_I2C lcd(0x27, 16, 2);

WiFiClient client;

void setup() {
  lcd.begin();
  lcd.backlight();
  Serial.begin(57600);
  Serial.println();

  /* Set Client up as station */
  WiFi.mode(WIFI_STA);

  WiFi.begin(NAME, PASS);

  /* Connect to the network */
  Serial.print("Connecting");
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  lcd.print(WiFi.localIP());
}

void loop() {
  if (client.connect(host, 5000))
  {
    Serial.print("Connected to: ");
    Serial.println(host);
    lcd.print(host);

    /* Send "connected" to the server so it knows we are ready for data */
    client.println("deviceconnected"); //USE client.println()!!
    Serial.println("Host message: \n");
    lcd.print("connected");

    /* Wait for data for 5 seconds at most before timing out */
    unsigned long timeout = millis();
    while(client.available() == 0)
    {
      if(millis() - timeout > 5000)
      {
        Serial.println("Timeout to server!");
        break;
      }
    }

    /* Read in the data in the stream */
    while(client.available() > 0)
    {
      Serial.println(client.readStringUntil('\n'));
      lcd.print(client.readStringUntil('\n'));
    }
    client.stop();
  }
  else
  {
    client.stop();
  }
  delay(5000);
}
