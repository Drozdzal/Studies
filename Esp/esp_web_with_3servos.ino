#include <Arduino.h>
#ifdef ESP32
  #include <WiFi.h>
  #include <AsyncTCP.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>
#include <Servo.h>

int servo1_value = 0;
int servo2_value = 0;
int servo3_value = 0;
bool s1_changed = false;
bool s2_changed = false;
bool s3_changed = false;

Servo servo1,servo2,servo3;

AsyncWebServer server(80);
const char* ssid = "UPC4627445";
const char* password = "wn88bAuxtrwS";

const char* input_parameter1 = "input_servo1_value";
const char* input_parameter2 = "input_servo2_value";
const char* input_parameter3 = "input_servo3_value";

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>HTML</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <head>
  <link rel="stylesheet" href="styles.css">
</head>
  </head>
  <body>
  <h2>Type 1 to move servo</h2> 
  <form action="/get">
    Servo_One: <input type="text" name="input_servo1_value">
    <input type="submit" value="Submit">
  </form><br>
  <form action="/get">
   Servo_Two: <input type="text" name="input_servo2_value">
    <input type="submit" value="Submit">
  </form><br>
  <form action="/get">
    Servo_Three: <input type="text" name="input_servo3_value">
    <input type="submit" value="Submit">
  </form>
</body></html>)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connecting...");
    return;
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String input_message;
    String input_parameter;

    if (request->hasParam(input_parameter1)) {
      input_message = request->getParam(input_parameter1)->value();
      input_parameter = input_parameter1;
      s1_changed = true;


    }
    else if (request->hasParam(input_parameter2)) {
      input_message = request->getParam(input_parameter2)->value();
      input_parameter = input_parameter2;
      s2_changed = true;
    }
    
    else if (request->hasParam(input_parameter3)) {
      input_message = request->getParam(input_parameter3)->value();
      input_parameter = input_parameter3;
      s3_changed = true;

    }
    else {
      input_message = "No message sent";
      input_parameter = "none";
    }
    Serial.println(input_message);
    request->send(200, "text/html", "HTTP GET request sent to your ESP on input field ("+ input_parameter + ") with value: " + input_message + "<br><a href=\"/\">Return to Home Page</a>");
  });
  server.onNotFound(notFound);
  server.begin();
  servo1.attach(14); 
  servo2.attach(13);
  servo3.attach(12);
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
}

int range = 100;
void loop() {
if(s1_changed)
{
    for (float pos = 0; pos <= range; pos += 0.5) 
    { // goes from 0 degrees to 180 degrees
        servo1.write(pos);              // tell servo to go to position in variable 'pos'      
        delay(10);   
    }

    for (float pos = range; pos >= 0; pos -= 0.5) 
      { // goes from 0 degrees to 180 degrees
      servo1.write(pos);              // tell servo to go to position in variable 'pos'
      delay(10);                       // waits 15ms for the servo to reach the position
      }
      Serial.println(1);
      s1_changed = false;
}

if(s2_changed)
{
    for (float pos = 0; pos <= range; pos += 0.5) { // goes from 0 degrees to 180 degrees
        servo2.write(pos);              // tell servo to go to position in variable 'pos'
        delay(10);           
    }// waits 15ms for the servo to reach the position
    for (float pos = range; pos >= 0; pos -= 0.5) 
      { // goes from 0 degrees to 180 degrees
      servo2.write(pos);              // tell servo to go to position in variable 'pos'
      delay(10);                       // waits 15ms for the servo to reach the position
      }
      Serial.println(2);
      s2_changed = false;
}

if(s3_changed)
{
    for (float pos = 0; pos <= range; pos += 0.5) { // goes from 0 degrees to 180 degrees
        servo3.write(pos);              // tell servo to go to position in variable 'pos'
        delay(10);           
    }// waits 15ms for the servo to reach the position
    for (float pos = range; pos >= 0; pos -= 0.5) 
      { // goes from 0 degrees to 180 degrees
      servo3.write(pos);              // tell servo to go to position in variable 'pos'
      delay(10);                       // waits 15ms for the servo to reach the position
      }
      Serial.println(3);
      s3_changed = false;
}

}
