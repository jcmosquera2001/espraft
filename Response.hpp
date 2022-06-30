#pragma once

#include <ESP8266WiFi.h>
#include "Arduino.h"
#include "ArduinoJson.h"
#include "RPC.hpp"

namespace locke {

class Response {
 public:
  // Member functions 
  Response(char[RESPONSE_BUFFER]);
  Response(bool, uint32_t, RPC::Type);
  bool success() const;
  uint32_t term() const;
  uint8_t type() const;
  void print();
  void send(WiFiClient);
 private:
  // Member variables 
  StaticJsonDocument<JSON_SMALL> doc;
};

}
