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
// Switch button
#define SW1  16  // Switch PIN 16
#define SW2  14  // Switch PIN 14

WiFiClient client;

// WIFI
char Wifi_Name[] = "true_home2G_DD2";         // Wifi Name
char Wifi_Pass[] = "0871234448";              // Wifi Password
// ThingSpeak
unsigned long Channel_ID = 1720954;         // Channel ID
const char * APIkey = "G83D5Z1Q8JMSTLMJ";   // Write API Key
// LINE Notify
char LINE_TOKEN[] = "n6osjXfpYtku6zHTFPMZdttkuoUJ1FC5hSt5f2t4c3U";  // LINE Token

Adafruit_8x16minimatrix matrix = Adafruit_8x16minimatrix();

float max_temp = 33;
float min_temp = 30;
float start_time1 , stop_time1, start_time2, stop_time2;
int state1 = 0;
int state2 = 0;
int buttonState11;
int buttonState12;

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

  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);
}

void loop() {
  float Temp = Temperature();
  LED_matrix(Temp, 0);
  buttonState11 = digitalRead(SW1);
  buttonState12 = digitalRead(SW2);
  button();
  // Thingspeak & LINE Notify
  ThingSpeak.setField(1, Temp);
  int Status = ThingSpeak.writeFields(Channel_ID, APIkey);
  if (Status == 200) {
    Serial.println("-----Update Successful-----");
    if (Temp >= max_temp) {
      //LINE.notify("แจ้งเตือน: อุณหภูมิสูงกว่าที่กำหนด " + String(Temp) + " °C");
      LINE.notifySticker("แจ้งเตือน: อุณหภูมิสูงกว่า " + String(max_temp) + " °C" + " ตอนนี้อุณหภูมิ " + String(Temp) + " °C", 11539, 52114142);
    } 
    else if (Temp <= min_temp) {
      //LINE.notify("แจ้งเตือน: อุณหภูมิต่ำกว่าที่กำหนด " + String(Temp) + " °C");
      LINE.notifySticker("แจ้งเตือน: อุณหภูมิต่ำกว่า " + String(min_temp) + " °C" + " ตอนนี้อุณหภูมิ " + String(Temp) + " °C", 2, 29);    
    }
  }
  else {
    Serial.println("---------------------------");
  }
  Serial.print("Temperature: ");
  Serial.println(Temp);
  delay(3000);
}
