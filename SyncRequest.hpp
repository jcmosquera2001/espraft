#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

#include "Constants.hpp"

namespace locke {

namespace SyncRequest {

typedef struct {
  bool success;
  uint32_t term;
} Result;

bool perform(IPAddress&, JsonObject, Result*);

}

}
