/*  Connects to the home WiFi network
    Asks some network parameters
    Starts WiFi server with fix IP and listens
    Receives and sends messages to the client
    Communicates: wifi_client_01.ino
*/
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <Servo.h>

#include <html_page.h>

byte ledPin = 2;
char ssid[] = "goldenboy";               // SSID of your home WiFi
char pass[] = "ambassadeur";               // password of your home WiFi
WiFiServer server(80);

const int LEDpin = D3;
const int delay_us = 13; // 38 KHz
int i;

IPAddress ip(192, 168, 43, 58);            // IP address of the server
IPAddress gateway(192, 168, 43, 129);        // gateway of your network
IPAddress subnet(255, 255, 255, 0);       // subnet mask of your network
float   x = 0 ;
float   y = 0 ;
float   z = 0;

Servo myservo; // create servo object to control a servo

void setup() {
  Serial.begin(115200);                   // only for debug

  myservo.attach(D1);  // attaches the servo on GIO2 to the servo object
  pinMode(LED_BUILTIN, OUTPUT);
  myservo.write(0);

  WiFi.config(ip, gateway, subnet);       // forces to use the fix IP
  WiFi.begin(ssid, pass);                 // connects to the WiFi router
  while (WiFi.status() != WL_CONNECTED) {
    delay(50);
    Serial.print(".");
  }
  Serial.println("Connected to wifi");
  Serial.print("Status: "); Serial.println(WiFi.status());  // some parameters from the network
  Serial.print("IP: ");     Serial.println(WiFi.localIP());
  Serial.print("Subnet: "); Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: "); Serial.println(WiFi.gatewayIP());
  Serial.print("SSID: "); Serial.println(WiFi.SSID());
  Serial.print("Signal: "); Serial.println(WiFi.RSSI());
  Serial.print("Networks: "); Serial.println(WiFi.scanNetworks());

  pinMode(LEDpin, OUTPUT);

  // Starts the server
  server.begin();
  Serial.println(F("Server started"));
  pinMode(ledPin, OUTPUT);
}

void takePhotoMechanical() {
  for (int i = 0 ; i < 3; i++) {
    myservo.write(20);
    delay(100);
    myservo.write(0);
    delay(100);
  }
}

void takePhotoLight() {
  for (i = 0; i < 76; i++) {
    digitalWrite(LEDpin, HIGH);
    delayMicroseconds(delay_us);
    digitalWrite(LEDpin, LOW);
    delayMicroseconds(delay_us);
  }
  delayMicroseconds(27880);

  for (i = 0; i < 16; i++) {
    digitalWrite(LEDpin, HIGH);
    delayMicroseconds(delay_us);
    digitalWrite(LEDpin, LOW);
    delayMicroseconds(delay_us);
  }

  delayMicroseconds(1486);

  for (i = 0; i < 16; i++) {
    digitalWrite(LEDpin, HIGH);
    delayMicroseconds(delay_us);
    digitalWrite(LEDpin, LOW);
    delayMicroseconds(delay_us);
  }

  delayMicroseconds(3484);

  for (i = 0; i < 16; i++) {
    digitalWrite(LEDpin, HIGH);
    delayMicroseconds(delay_us);
    digitalWrite(LEDpin, LOW);
    delayMicroseconds(delay_us);
  }
}

void loop () {
  WiFiClient client = server.available();
  if (client) {
    if (client.connected()) {
      Serial.print("\nclient is connected");
      Serial.print("client still connected");
      digitalWrite(ledPin, LOW);  // to show the communication only (inverted logic)
      String request = client.readStringUntil('\r');    // receives the message from the client
      Serial.print("From client: ");
      Serial.println(request);

      int val;
      if (request.indexOf(F("/takephoto/1")) != -1) {
        int j = 0;
        //for ( j = 0; j < 3 ; j++) {
          takePhotoLight();
          delay(30);
        //}
        Serial.print("taking photo");
      } else if (request.indexOf(F("/gpio/0")) != -1) {
        digitalWrite(LED_BUILTIN, 0);
        delay(500);
        digitalWrite(LED_BUILTIN, 1);
        delay(500);
        digitalWrite(LED_BUILTIN, 0);
        delay(500);
        digitalWrite(LED_BUILTIN, 1);
        delay(500);
        val = 0;

      } else if (request.indexOf(F("/gpio/1")) != -1) {
        val = 1;
      } else {
        Serial.print(F("invalid request: "));
        Serial.println(request);
        val = digitalRead(LED_BUILTIN);
      }

      // Set LED according to the request
      digitalWrite(LED_BUILTIN, val);

      /*client.print(F("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nPhoto is now "));
        client.print(F("<br><br>Click <a href='http://"));
        client.print(WiFi.localIP());
        client.print(F("/takephoto/1'>here</a> take photo </html>"));*/
      client.print(getPage());
      digitalWrite(ledPin, HIGH);
    }
    //client.stop();                // tarminates the connection with the client
  }
}
