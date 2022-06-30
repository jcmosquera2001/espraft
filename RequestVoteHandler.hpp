#pragma once

#include "RaftServer.hpp"
#include "Log.hpp"
#include "RequestVote.hpp"

namespace locke {

class RequestVoteHandler {
 public:
  RequestVoteHandler(RaftServer&, const RequestVote&);
  void process(WiFiClient);
 private:
  void reply(WiFiClient,bool);
  RaftServer& server;
  const RequestVote& req;
};

}
