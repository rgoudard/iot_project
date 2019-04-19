# iot_project

## Project scope

Our project aims to take picture from a Nikon D5300 whenever someone who wears our sensor falls (while climbing for example).
We are using an accelerometer to "catch" falls or any fast movements, so we could also take photo of a balls throwed or something else, sky's the limit.

## Used materials

To achieve this project we used: 

•    A camera [Nikon, model 5300](https://www.nikon.fr/fr_FR/product/digital-cameras/slr/consumer/d5300-black).

•    An [InfraRed remote control](https://www.fnac.com/Nikon-telecommande-ML-L3/a1801482/w-4)

•    Two [Wemos R1D1mini](https://www.banggood.com/WeMos-D1-Mini-V2-NodeMcu-4M-Bytes-Lua-WIFI-Internet-Of-Things-Development-Board-Based-ESP8266-p-1115398.html?cur_warehouse=CN)

•    Two externals batteries 

•    One [micro servo SG90](https://boutique.semageek.com/fr/104-micro-servo-tower-pro-sg90.html)

•    One resistance

•    One transitor

•    One [breadboard](https://www.amazon.fr/breadboard/s?k=breadboard)

•    One [InfraRed transmitter](https://www.makerfabs.com/IR-Transmitter.html)

•    One [accelerometer](https://shop.mchobby.be/fr/breakout/127-accelerometre-3-axes-sortie-analogique--3232100001275-adafruit.html)

## Used library:

### Client :
  
  •    <MPU6050_tockn.h>    -> library for easy communication with the [MPU6050](https://www.amazon.fr/Capteur-MPU-6050-Module-analogique-acc%C3%A9l%C3%A9rom%C3%A8tre/dp/B00E1EQXL6).
  
  •    <Wire.h>             -> This library allows you to communicate with I2C / TWI devices.
  
  •    <SPI.h>              -> Serial Peripheral Interface (SPI) is a synchronous serial data protocol used by microcontrollers for communication.
  
  •    <ESP8266WiFi.h>      -> If you are eager to connect your new ESP8266 module to Wi-Fi network to start sending and receiving data.

### Server :

  •    <SPI.h>              -> Serial Peripheral Interface (SPI) is a synchronous serial data protocol used by microcontrollers for communication.
  
  •    <ESP8266WiFi.h>      -> If you are eager to connect your new ESP8266 module to Wi-Fi network to start sending and receiving data.
  
  •    <Servo.h>            -> This library allows an Arduino board to control RC (hobby) servo motors.

### Python :
  
  •    Airnef ([Open Source project](http://www.testcams.com/airnef/))
  
  •    FTPLib

### Cloud :

  Html / CSS / PHP / OVH

## Deployement diagram: 

![](https://i.ibb.co/wcF8Q9W/diagramme-deploiement.png)

Our system has 3 or 4 major components depending if we use a micro servo or an IR transmitter: 
  - The client send a signal whenever someone fall.
  - The server receive the client signal and do an anction in response. Depending on the user choice, the server can activate an IR remote controle with a press from a micro servo or directly by sending an IR signal to the camera.
  - The remote control is activated by the micro servo which send the IR signal to the camera.
  - The camera take a picture when receiving the IR signal.

We finally chose the 3 composants option without the micro servo for performance reasons.

## Client:
schema:
![](https://i.ibb.co/k5nJmZz/image02.png)

picture:
![](https://i.ibb.co/Y8RLyFH/DSC-0100.jpg)


The client is equiped with an accelerometer to mesire accelerations from differents axis(X, Y, Z). When a fall occur, those three axis values tend to zero. We have then created a condition on those values. To never miss a fall and try to avoid mistakes, we didn't put 0.0 in the condition but we put a threshold of 0.3. 
When we detect a fall, we send a Wifi message to the server to the address takephoto/1 .

## Server + transmitter IR:
schema:
![schema](https://i.ibb.co/bXFnqfL/image01.png)

picture:
![picture](https://i.ibb.co/2SWD4g3/DSC-0106.jpg)

The Wifi server listen to request. 
When a request is received on takephoto/1, we enter the takePhotoLight() function and by digitaly writing on the LED pin, an IR signal is sent to the camera that make it take a picture.


## Server + Micro servo + IR remote controller:
schema:
![](https://i.ibb.co/YQPKDR8/image.png)

picture:
![](https://i.ibb.co/S5XzFFG/DSC-0108.jpg)

The wifi server is the same as with the IR transmitter, it is listening to requests.
When a request is received on takephoto/1, this time we enter the takePhotoMechanical() function which activate a micro servo that push a button on a remote controller who then send an IR signal to the camera and finally take a picture.

If you want to know more about it, check out this [link](https://www.christidis.info/index.php/personal-projects/arduino-nikon-infrared-command-code)

## Work team schedule:

![](https://i.ibb.co/vwqH4wt/Capture.png)


To make it work, we first tried to take a photo and retreive it wia the Wifi network of the camera, so we tried to retro engeneere the APK but it was too complex and we decided to move on to sometinh else.

So we tried to retro ingeneere a C# code but it also didn't worked, the code version wasn't compatible with our camera model. But, at least we succeeded in retreiving some signal codes.

We then tried to reproduce the InfraRed signal that remote controllers produce with an IR transmitter by analysing it with a logic analyser.

![](https://i.ibb.co/PzdNnfj/Screenshot-from-2019-04-17-18-09-41.png)

First we tried to make it work with 5V but intensity was too high and the LED burned, so we went for the 3V alimentation but it was not enough to power it. So we had variation on the signal and it wasn't working. To make it work we had to use a transistor and a resistance to have a correct signal by boosting the 3V.

We then tried the micro servo to activate a remote controller via a mechanical push.

The two Wemos are communicating via Wifi, whenever the accelerometer is in freefall, a request is passed to the server that send multiple IR signals via the transmitter and the camera take pictures.

A python server retreive the pictures from the camera Wifi network and send it to a website in the cloud.

To do that, the python server need to be connected to internet and the Camera Wifi. To launch this service you need to go in the PhotoTransfer directory then type in your console :

`python airnefcmd.py --outputdir="./outputs" --realtimedownload="only" --downloadexec python ./ftpUpload.py @pf@ @filename@ [FTP_HOST] [FTP_USER] [FTP_PASSWORD] [FTP_DESTINATION]`

## Cloud:

After being download, pictures are send by FTP to the OVH server. Pictures are display on http://draweverythinggame.com/

If you want to reprodu ce this project for free, you can remove the python code that does the uploading: 
`python airnefcmd.py --outputdir="./outputs" --realtimedownload="only" --downloadexec`
pictures will be download on the directory output. After that you can host them in a locally setted website.
For more simplicity you can search for a portfolio template.
