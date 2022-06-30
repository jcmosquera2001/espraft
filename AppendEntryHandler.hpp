#pragma once

#include "RaftServer.hpp"
#include "Log.hpp"
#include "AppendEntry.hpp"

namespace locke {

class AppendEntryHandler {
 public:
  // Member functions 
  AppendEntryHandler(RaftServer&, const AppendEntry&);
  void process(WiFiClient);
 private:
  void update_server();
  void try_append(WiFiClient);
  void append(WiFiClient);
  void reply(WiFiClient,bool);
  // Member variables 
  RaftServer& server;
  const AppendEntry& req;
};

}
