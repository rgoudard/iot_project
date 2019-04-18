# iot_project

## Project scope

Our project aims to take picture from a Nikon D5300 whenever someone who wear our captor fall. 

## Used materials

To achieve this project we used: 

•    A camera Nikon, model 5300.

•    An InfraRed remote control

•    Two Wemos R1D1mini

•    Two externals batteries

•    One micro servo SG90

•    One resistance

•    One transitor

•    One breadboard

•    One InfraRed transmitter

•    One InfraRed receptor

•    One accelerometer


## Deployement diagram: 

https://ibb.co/q59n395

Our system has 3 or 4 major components depending if we use a micro servo or an IR transmitter: 
  - The client send a signal whenever someone fall.
  - The server receive the client signal and do an anction in response. Depending on the user choice, the server can activate an IR remote controle with a press from a micro servo or directly by sending an IR signal to the camera.
  - The remote control is activated by the micro servo which send the IR signal to the camera.
  - The camera take a picture when receiving the IR signal.

We finally chose the 3 composants option without the micro servo for performance reasons.

## Client:

https://ibb.co/1MnFLSw

The client is equiped with an accelerometer to mesire accelerations from differents axis(X, Y, Z). When a fall occur, those three axis values tend to zero. We have then created a condition on those values. To never miss a fall and try to avoid mistakes, we didn't put 0.0 in the condition but we put a threshold of 0.3. 
When we detect a fall, we send a Wifi message to the server to the address takephoto/1 .

## Server + transmitter IR:

https://ibb.co/qpCwXZ9

The Wifi server listen to request. 
When a request is received on takephoto/1, we enter the takePhotoLight() function and by digitaly writing on the LED pin, an IR signal is sent to the camera that make it take a picture.


## Server + Micro servo + IR remote controller:

https://ibb.co/Gpn1sxk

The wifi server is the same as with the IR transmitter, it is listening to requests.
When a request is received on takephoto/1, this time we enter the takePhotoMechanical() function which activate a micro servo that push a button on a remote controller who then send an IR signal to the camera and finally take a picture.

## Work team schedule:

https://ibb.co/98gNH8M


To make it work, we first tried to take a photo and retreive it wia the Wifi network of the camera, so we tried to retro engeneere the APK but it was too complex and we decided to move on to sometinh else.

So we tried to retro ingeneere a C# code but it also didn't worked, the code version wasn't compatible with our camera model. But, at least we succeeded in retreiving some signal codes.

We then tried to reproduce the InfraRed signal that remote controllers produce with an IR transmitter by analysing it with an oscilloscope.

First we tried to make it work with 5V but intensity was too high and the LED burned, so we went for the 3V alimentation but it was not enough to power it. So we had variation on the signal and it wasn't working. To make it work we had to use a transistor and a resistance to have a correct signal by boosting the 3V.

We then tried the micro servo to activate a remote controller via a mechanical push.

The two Wemos are communicating via Wifi, whenever the accelerometer is in freefall, a request is passed to the server that send multiple IR signals via the transmitter and the camera take pictures.

A python server retreive the pictures from the camera Wifi network and send it to a website in the cloud.


 
