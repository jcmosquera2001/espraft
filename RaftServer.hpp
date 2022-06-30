#pragma once

#include "Arduino.h"
#include "Constants.hpp"
#include "Peer.hpp"

namespace locke {

enum State {
  Follower,
  Candidate,
  Leader
};

class RaftServer {
 public:
  // Member functions 
  RaftServer(char);
  State get_status();
  void set_status(State);
  void update_election_timeout();
  bool should_become_candidate();
  void setup();
  void save();
  void restore();
  void dump();
  
  // Member variables 
  uint32_t current_term;
  uint32_t last_index;
  uint32_t commit_index;
  char voted_for;
  char leader;
  Peer* peers[NUM_PEERS];
  const char name;
 private:
  State _status;
  uint32_t _election_timeout;
};

}
