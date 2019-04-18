/*  Connects to the home WiFi network
    Asks some network parameters
    Starts WiFi server with fix IP and listens
    Receives and sends messages to the client
    Communicates: wifi_client_01.ino
*/
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <Servo.h>

//byte ledPin = 2;
char ssid[] = "goldenboy";               // SSID of your home WiFi
char pass[] = "ambassadeur";               // password of your home WiFi
WiFiServer server(80);

const int LEDIR = D3;
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

  //pinMode(ledPin, OUTPUT);

  // Starts the server
  server.begin();
  Serial.println("Server started");
  //pinMode(ledPin, OUTPUT);
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
  digitalWrite(LED_BUILTIN, HIGH);
  for (i = 0; i < 76; i++) {
    digitalWrite(LEDIR, HIGH);
    delayMicroseconds(delay_us);
    digitalWrite(LEDIR, LOW);
    delayMicroseconds(delay_us);
  }
  delayMicroseconds(27880);

  for (i = 0; i < 16; i++) {
    digitalWrite(LEDIR, HIGH);
    delayMicroseconds(delay_us);
    digitalWrite(LEDIR, LOW);
    delayMicroseconds(delay_us);
  }

  delayMicroseconds(1486);

  for (i = 0; i < 16; i++) {
    digitalWrite(LEDIR, HIGH);
    delayMicroseconds(delay_us);
    digitalWrite(LEDIR, LOW);
    delayMicroseconds(delay_us);
  }

  delayMicroseconds(3484);

  for (i = 0; i < 16; i++) {
    digitalWrite(LEDIR, HIGH);
    delayMicroseconds(delay_us);
    digitalWrite(LEDIR, LOW);
    delayMicroseconds(delay_us);
  }
  digitalWrite(LED_BUILTIN, LOW);
}

WiFiClient client;

void loop () {
  if(!client)
    client = server.available();
  if (client) {
    Serial.println("Client connected");
    if (client.connected()) {
      Serial.println("client is connected");
      //digitalWrite(ledPin, LOW);  // to show the communication only (inverted logic)
      String request = client.readStringUntil('\r');    // receives the message from the client
      Serial.print("From client: ");
      Serial.println(request);

      int val;
      if (request.indexOf("/takephoto/1") != -1) {
        int j = 0;
        for ( j = 0; j < 10 ; j++) {
          takePhotoLight();
        }
        //takePhotoMechanical();
        Serial.println("taking photo");
      } else {
        Serial.print("invalid request: ");
        Serial.println(request);
      }
      
      client.stop();
    }
  }
}
