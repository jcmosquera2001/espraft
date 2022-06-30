#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Arduino.h>
#include "user_interface.h"

#define LEADER_LED 4
#define ALIVE_LED 0

long lastTime=0;
//const char* ssid = "open";
//const char* password = "2160337400";

WiFiUDP Udp;
IPAddress multicastAddress(226,1,197,1);
unsigned int localUdpPort = 50000;  // local port to listen on
char  incomingPacket[255];  // buffer for incoming packets

char id='1';
char myID[] = "1"; 
char currentLeader = id;

void old_loop()
{
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    // receive incoming UDP packets
    Serial.printf("Received %d bytes from %s, port %d destination IP %s\n", 
                   packetSize, Udp.remoteIP().toString().c_str(), 
                   Udp.remotePort(), 
                   Udp.destinationIP().toString().c_str());
    int len = Udp.read(incomingPacket, 255);
    if (len > 0) {
      incomingPacket[len] = 0;
    }
    Serial.printf("UDP packet contents: %s\n", incomingPacket);

    if (incomingPacket[0]>=currentLeader) {
      currentLeader=incomingPacket[0];
      lastTime = millis();
      digitalWrite(ALIVE_LED,!digitalRead(ALIVE_LED)); // blink
      digitalWrite(LEADER_LED, HIGH); // OFF
    } else {
      if (currentLeader==id) {
        /* I'm the leader */
        Udp.beginPacketMulticast(multicastAddress, localUdpPort, WiFi.localIP());
        Udp.write(myID);
        Udp.endPacket();
        lastTime = millis();
        digitalWrite(LEADER_LED, !digitalRead(LEADER_LED)); // blink
        digitalWrite(ALIVE_LED, HIGH); // OFF
      }
    }
  } else {
    /* Keep Alive if I'm the leader */
    if (currentLeader==id) {
      if (millis()-lastTime > 2000) {
        Serial.printf("I'm leader\n");
        Udp.beginPacketMulticast(multicastAddress, localUdpPort, WiFi.localIP());
        Udp.write(myID);
        Udp.endPacket();
        lastTime = millis();
        digitalWrite(LEADER_LED, !digitalRead(LEADER_LED)); // blink
        digitalWrite(ALIVE_LED, HIGH); // OFF
      }
    } else {
      /* The leader is dead! I'm the new leader! */
      if (millis() - lastTime > 5000) {
        Serial.printf("Leader is dead!\n");
        currentLeader = id;
        Udp.beginPacketMulticast(multicastAddress, localUdpPort, WiFi.localIP());
        Udp.write(myID);
        Udp.endPacket();
        lastTime = millis();
        digitalWrite(LEADER_LED, !digitalRead(LEADER_LED)); // blink
        digitalWrite(ALIVE_LED, LOW); // ON
      }
    }

  }
  
}

void old_setup()
{
  Serial.begin(115200);
  Serial.println();

  pinMode(LEADER_LED, OUTPUT); 
  pinMode(ALIVE_LED,  OUTPUT); 
  digitalWrite(LEADER_LED, HIGH);
  digitalWrite(ALIVE_LED,  HIGH);
  
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");

  Udp.beginMulticast(WiFi.localIP(), multicastAddress, localUdpPort);
  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);
  lastTime = millis();
}