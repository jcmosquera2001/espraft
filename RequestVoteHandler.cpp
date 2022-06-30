#include "RequestVoteHandler.hpp"
#include "Response.hpp"

using namespace locke;

RequestVoteHandler::RequestVoteHandler
(RaftServer& server, const RequestVote& req) : server(server), req(req) {}

void RequestVoteHandler::process(WiFiClient client)
{
  if (req.term() < server.current_term) {
    Serial.println("menor term");
    reply(client,false);
    return;
  }

  Serial.print("req.candidate=");Serial.println((int)req.candidate());
  // esta mal, si term rx > server.term hay q aceptar voto
  if (server.voted_for != NOBODY_YET && server.voted_for != req.candidate()) {
    Serial.println("vote por otro");
    reply(client,false);
    return;
  }

  Log::Entry last_entry;
  Log::last(&last_entry);

  Serial.print("Last entry i=");Serial.print(last_entry.idx);
  Serial.print(" t=");Serial.print(last_entry.term);
  Serial.print(" v=");Serial.println(last_entry.value);
  
  if (last_entry.term > req.last_term()) {
    Serial.println("last term menor");
    reply(client,false);
    return;
  }

  if (last_entry.term == req.last_term() && last_entry.idx > req.last_index()) {
    Serial.println("last index menor");
    reply(client,false);
    return;
  }

  server.voted_for = req.candidate();
  server.save();

  reply(client,true);
}

void RequestVoteHandler::reply(WiFiClient client,bool success)
{
  Response response(success, server.current_term, RPC::RequestVoteResponse);
  response.send(client);
  //response.print();
}
