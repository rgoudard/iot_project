/*  Connects to the home WiFi network
    Asks some network parameters
    Sends and receives message from the server in every 2 seconds
    Communicates: wifi_server_01.ino
*/
#include <MPU6050_tockn.h>
#include <Wire.h>
#include <SPI.h>
#include <ESP8266WiFi.h>

TwoWire i2c;

char ssid[] = "goldenboy";           // SSID of your home WiFi
char pass[] = "ambassadeur";            // password of your home WiFi


IPAddress server(192, 168, 43, 58);    // the fix IP address of the server
WiFiClient client;

MPU6050 mpu6050(i2c);

void setup() {
  Serial.begin(115200);               // only for debug
  WiFi.begin(ssid, pass);             // connects to the WiFi router

  i2c.begin(D3, D4);
  mpu6050.begin();

  if (client.connect(server, 80)) {
    // Connection to the server
    Serial.println("Connected");
  } else {
    Serial.println("Can't connect");
  }
}

void loop () {
  if (!client.connected()) {
    if (client.connect(server, 80)) {
      // Connection to the server
      Serial.println("RE - Connected");
    } else {
      Serial.println("Can't connect");
    }
  }
  mpu6050.update();

  if (-0.3 <= mpu6050.getAccX() && mpu6050.getAccX() <= 0.3) {
    if (-0.3 <= mpu6050.getAccY() && mpu6050.getAccY() <= 0.3) {
      if (-0.3 <= mpu6050.getAccZ() && mpu6050.getAccZ() <= 0.3) {

        if (client.connected())
          client.println("GET /takephoto/1 HTTP/1.0");  // sends the message to the server
        Serial.println("ok");
      }
    }
  }
}
