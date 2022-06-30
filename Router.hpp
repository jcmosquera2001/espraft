#pragma once

#include <ESP8266WiFi.h>
#include "Constants.hpp"
#include "RaftServer.hpp"
#include "RPC.hpp"
#include "ArduinoJson.h"

namespace locke {

class Router {
 public:
  Router(WiFiServer&, RaftServer&);
  void handle_request();
 private:
  void listen(WiFiClient&, char[REQUEST_BUFFER]);
  uint8_t rpc_type(JsonObject);
  WiFiServer& tcp_svr;
  RaftServer& raft_svr;
};

}
