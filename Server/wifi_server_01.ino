/*  Connects to the home WiFi network
    Asks some network parameters
    Starts WiFi server with fix IP and listens
    Receives and sends messages to the client
    Communicates: wifi_client_01.ino
*/
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <Servo.h>

char ssid[] = "goldenboy";               // SSID of your home WiFi
char pass[] = "ambassadeur";               // password of your home WiFi
WiFiServer server(80);

IPAddress ip(192, 168, 43, 58);            // IP address of the server
IPAddress gateway(192, 168, 43, 129);        // gateway of your network
IPAddress subnet(255, 255, 255, 0);       // subnet mask of your network

Servo myservo; // create servo object to control a servo

void setup() {
  Serial.begin(115200);                   // only for debug

  myservo.attach(D1);  // attaches the servo on GIO2 to the servo object
  pinMode(LED_BUILTIN, OUTPUT);
  myservo.write(0);

  WiFi.config(ip, gateway, subnet);       // forces to use the fix IP
  WiFi.begin(ssid, pass);                 // connects to the WiFi router
  while (WiFi.status() != WL_CONNECTED) { // print "." until connected to wifi
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

  // Starts the server
  server.begin();
  Serial.println("Server started");
}

//Moves servomotor to activate the remote control
void takePhotoMechanical() {
  for (int i = 0 ; i < 3; i++) {
    myservo.write(20);
    delay(100);
    myservo.write(0);
    delay(100);
  }
}

WiFiClient client;

void loop () {
  if(!client)
    client = server.available();
  if (client) {
    Serial.println("Client connected");
    if (client.connected()) {
      Serial.println("client is connected");
      String request = client.readStringUntil('\r');    // receives the message from the client
      Serial.print("From client: ");
      Serial.println(request);

      int val;
      //filter the client request
      if (request.indexOf("/takephoto/1") != -1) { 
        takePhotoMechanical();
        Serial.println("taking photo");
      } else {
        Serial.print("invalid request: ");
        Serial.println(request);
      }
      
      client.stop();
    }
  }
}
