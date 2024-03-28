static const uint8_t D0   = 16;
static const uint8_t D1   = 5;
static const uint8_t D2   = 4;
static const uint8_t D3   = 0;
static const uint8_t D4   = 2;
static const uint8_t D5   = 14;
static const uint8_t D6   = 12;
static const uint8_t D7   = 13;
static const uint8_t D8   = 15;
static const uint8_t D9   = 3;
static const uint8_t D10  = 1;
#include <Robojax_L298N_DC_motor.h>
// thiết lập motor 1 và 2
#define IN1 D6
#define IN2 D7
#define IN3 D5
#define IN4 D4
#define ENA1 D8 //pin điều khiển tốc độ
#define ENA2 D2
const int CCW = 2; 
const int CW  = 1; 
int motorDirection = CW;
#define motor1 1
#define motor2 1

Robojax_L298N_DC_motor motor_one(IN1, IN2, ENA1, true);
Robojax_L298N_DC_motor motor_two(IN3, IN4, ENA2, true);
String accessName ="robojaxESP8266";
const int changeStep = 5;
int outPutValue = 40;
const int motorMinimumSpeed=20;
int motor1StopState=HIGH;
int motor2StopState=HIGH;
#include "robojax_speed_start_stop_control_page.h"

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#ifndef STASSID
#define STASSID "MyCrushBirthday"
#define STAPSK  "15052002"
#endif

const char *ssid = STASSID;
const char *password = STAPSK;

ESP8266WebServer server(80);

void handleRoot() 
{
  String HTML_page = speed_control_page_part1;  
  HTML_page.concat(outPutValue);  
  HTML_page.concat(speed_control_page_part2);  
  HTML_page.concat(outPutValue);
  HTML_page.concat(speed_control_page_part3);
 
  server.send(200, "text/html", HTML_page);
}

void handleNotFound() 
{
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++) 
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
}

void setup(void) 
{
  Serial.begin(9600);
  motor_one.begin();
  motor_two.begin();
    
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin(accessName)) 
  {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/speed", HTTP_GET, handleMotorSpeed);  
  server.on("/stop", HTTP_GET, handleMotorBrake);        
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) 
{  
  server.handleClient();
  MDNS.update();

  if(motor1StopState ==HIGH)
  {
    motor_one.brake(motor1);  
    motor_two.brake(motor2);     
  }
  else
  {
     motor_one.rotate(motor1, outPutValue, motorDirection);
     motor_two.rotate(motor2, outPutValue, motorDirection);
  }
  delay(100);
}

void handleMotorSpeed() 
{
  if(server.arg("do") == "slower")
  {
    outPutValue -=changeStep;    
      if(outPutValue < motorMinimumSpeed)
      {
        outPutValue = motorMinimumSpeed;
      }
  }
  else
  {
    outPutValue +=changeStep;        
      if(outPutValue > 100)
      {
        outPutValue =100;
      } 
  }
  handleRoot();
}

void handleMotorBrake() 
{
  if(server.arg("do") == "START")
  {  
      motor1StopState=LOW;
      motor2StopState=LOW;
  }
  else
  {
      motor1StopState=HIGH;    
      motor2StopState=HIGH; 
  }
  handleRoot();
}
