#include "AppendEntryHandler.hpp"
#include "Response.hpp"

using namespace locke;

AppendEntryHandler::AppendEntryHandler(RaftServer& server, 
        const AppendEntry& req) : server(server), req(req) {}

void AppendEntryHandler::process(WiFiClient client)
{
  
  if (req.term() < server.current_term) {
    reply(client,false);
    return;
  }

  update_server();

  if (req.isHeartbeat()) {
    // Serial.println("isHeartbeat");
    reply(client,true);
    return;
  }

  try_append(client);
}

void AppendEntryHandler::update_server()
{
  server.set_status(Follower);
  server.update_election_timeout();
  server.current_term = req.term();
  server.leader = req.leader();
  server.save();
}

void AppendEntryHandler::try_append(WiFiClient client)
{
  // Serial.println("try_append");
  Log::Entry prev;
  bool prev_found = Log::fetch(&prev, req.prev_index());

  if (!prev_found) {
    // Serial.println("prev inx not found");
    reply(client,false);
    return;
  }

  // Serial.print("Log prev.term=");Serial.println(prev.term);
  // Serial.print("Log prev.idx=");Serial.println(prev.idx);

  if (prev.term != req.prev_term() || prev.idx != req.prev_index()) {
    // Serial.println("truncate to prev inx");
    Log::truncate(prev.idx);
    reply(client,false);
    return;
  }

  append(client);
  
}

void AppendEntryHandler::append(WiFiClient client)
{
  uint32_t idx = req.prev_index() + 1;

  Log::Entry new_entry;
  Log::truncate(idx);
  Log::prepare(&new_entry, idx, req.term(), req.entry());
  Log::append(&new_entry);

  server.last_index = idx;
  server.save();

  reply(client,true);
}

void AppendEntryHandler::reply(WiFiClient client,bool success)
{
  Response response(success, server.current_term, RPC::AppendEntryResponse);
  response.send(client);
  // enviar respuesta
}
