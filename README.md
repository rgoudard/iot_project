# iot_project

Définition du projet

Notre projet consiste à déclencher la prise de photo d'un appareil Nikon D5300 lors de la chute d'un capteur porté par un utilisateur.


Matériels Utilisé

Pour réaliser ce projet nous avons eu besoin :

•    D'un appareil photo de la marque Nikon, modèle 5300.

•    D'une télécommande IR

•    Deux Wemos

•    Deux batteries externes

•    Un Cerveau Moteur SG90

•    Une résistance

•    Un transistor

•    Une breadboard

•    Un émetteur IR

•    Un récepteur IR

•    Un accéléromètre


Diagramme de déploiement: 
https://ibb.co/q59n395

Notre système comporte 3 ou 4 composants majeurs selon le cas utilisé pour tranférer le signal evoyé par le client : 
  - Le client qui envoie un signal lorsque que le peronne le portant chute.
  - Le serveur recevant le signal du client et qui déclanche une action à la reception. Selon le choix de l'utilisateur, le serveur peut déclancher un moteur pour activer une télécommande IR ou directement envoyer un signal IR à l'appareil photo.
  - La télécommande qui est déclanchée par le moteur et qui envoie le signal IR à l'appareil photo.
  - L'appareil photo qui prend une photo à la recpetion du signal IR. 

Le choix à 3 composants sans la télécommande a été retenu par notre groupe pour des raisons de performance.

Client:
https://ibb.co/1MnFLSw

Le client est équipé d'un accéléromètre pour mesurer les accélarations des différents axes(X, Y et Z). Lors d'une chute toutes ces données convergent vers 0. Nous avons donc créé une condition sur les valeurs de ces données. Pour des soucis de précision et afin d'éviter les erreurs, nous n'avons pas mis exactement 0 mais nous avons mis un seuil de tolérence qui entoure légèrement 0. 

Serveur+Emetteur IR:
https://ibb.co/qpCwXZ9



Serveur+Moteur + télécommande IR:
https://ibb.co/Gpn1sxk

Gestion du temps de travail:
https://ibb.co/PjBGLpP
