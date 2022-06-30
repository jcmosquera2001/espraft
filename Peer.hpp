#pragma once

#include <ESP8266WiFi.h>
#include "Election.hpp"
#include "Election.hpp"

namespace locke {

class Peer {
 public:
  Peer(char, IPAddress&);
  Election::Vote vote;
  bool will_timeout_soon();
  bool pending_vote();
  bool enabled();
  void retry_later();
  void setup(uint32_t);
  void touch();
  uint32_t last_heartbeat;
  uint32_t next_index;
  uint32_t match_index;
  uint32_t retry_after;
  char name;
  IPAddress& ip;
};

}
