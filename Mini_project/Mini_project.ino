#include <Wire.h>
#include <WiFi.h>
#include <ThingSpeak.h>           // Thingspeak Lib
#include <TridentTD_LineNotify.h> // LINE Notify Lib
#include <Adafruit_GFX.h>         // LED GFX Lib
#include <Adafruit_LEDBackpack.h> // LED Lib
// Temperature Sensor
#define I2C_SDA1 4
#define I2C_SCL1 5
#define TEMP_ADDR 0x4D  // Temperature address
// LED matrix
#define I2C_SDA0 21
#define I2C_SCL0 22
#define LED_ADDR 0x70  // LED address

WiFiClient client;

// WIFI
char Wifi_Name[] = "___________";         // Wifi Name
char Wifi_Pass[] = "___________";              // Wifi Password
// ThingSpeak
unsigned long Channel_ID = 1720954;         // Channel ID
const char * APIkey = "___________";   // Write API Key
// LINE Notify
char LINE_TOKEN[] = "___________";  // LINE Token

Adafruit_8x16minimatrix matrix = Adafruit_8x16minimatrix();

void setup() {
  Serial.begin(115200); 
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
  Serial.println("Connecting to ");
  Serial.println(Wifi_Name);
  WiFi.begin(Wifi_Name, Wifi_Pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("-----WiFi Connected-----");

  LINE.setToken(LINE_TOKEN);          // define LINE Token
}

void loop() {
  float Temp = Temperature();
  ThingSpeak.setField(1, Temp);
  int Status = ThingSpeak.writeFields(Channel_ID, APIkey);
  if (Status == 200) {
    Serial.println("-----Update Successful-----");
    if (Temp >= 32) {
      //LINE.notify("แจ้งเตือน: อุณหภูมิสูงกว่าที่กำหนด " + String(Temp) + " °C");
      LINE.notifySticker("แจ้งเตือน: อุณหภูมิสูงกว่าที่กำหนด " + String(Temp) + " °C", 11539, 52114142);
    } 
    else if (Temp <= 31) {
      //LINE.notify("แจ้งเตือน: อุณหภูมิต่ำกว่าที่กำหนด " + String(Temp) + " °C");
      LINE.notifySticker("แจ้งเตือน: อุณหภูมิต่ำกว่าที่กำหนด " + String(Temp) + " °C", 2, 29);    
    }
  }
  else {
    Serial.println("---------------------------");
  }
  Serial.print("Temperature: ");
  Serial.println(Temp);
  
  LED_matrix();  
}
