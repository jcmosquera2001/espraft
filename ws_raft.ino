#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Arduino.h>
#include <FS.h>
#include "user_interface.h"

#include "Locke.h"

const char* ssid = "Fibertel WiFi842 2.4GHz";
const char* password = "0142004527";

// const char* ssid = "BVC_LINKSYS";
// const char* password = "stm32franju";

RaftServer raftserver('1');
WiFiServer TCPserver(RAFT_PORT);

void setup() {
  SPIFFS.begin();
  Serial.begin(115200);
  Serial.println();

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");
  Serial.println(WiFi.localIP());

  // Initialize raft components
  raftserver.setup();
  TCPserver.begin();
  raftserver.dump();
}	

void loop() {
  // process messages from other raft servers in cluster
  Router router(TCPserver, raftserver);
  router.handle_request(); 
  
  // process own raft server logic
  switch (raftserver.get_status()) {
    // this server is the leader 
    case State::Leader: {
      LogReplication replicate(raftserver);
      replicate.execute(); // envia un heartbeat si algun nodo esta a - de la mitad de vencer
      } break;
    // as Follower check expiration 
    case State::Follower:
      if (raftserver.should_become_candidate()) {
        //raftserver.set_status(Candidate);
      }
      break;
    // as Candiate try to get the votes
    case State::Candidate:
	    //LeaderElection::execute();
      break;
  }
  
}