#include "Router.hpp"
#include "AppendEntry.hpp"
#include "AppendEntryHandler.hpp"
#include "RequestVote.hpp"
#include "RequestVoteHandler.hpp"

using namespace locke;

Router::Router(WiFiServer& tcp_svr, RaftServer& raft_svr) :
    tcp_svr(tcp_svr), raft_svr(raft_svr) {}

void Router::handle_request()
{
  WiFiClient client = tcp_svr.available();

  if (!client) return;

  StaticJsonDocument<JSON_LARGE> doc;
  char msg_buff[REQUEST_BUFFER];
  listen(client, msg_buff);
  deserializeJson(doc, msg_buff);
  JsonObject json = doc.as<JsonObject>();
  RPC::Type rpc = (RPC::Type)rpc_type(json);

  if (rpc == RPC::AppendEntry) {
      AppendEntry append_entry(json);
      AppendEntryHandler handler(raft_svr, append_entry);
      handler.process(client);
      // agregar reply
  } else if (rpc == RPC::RequestVote) {
      RequestVote request_vote(json);
      RequestVoteHandler handler(raft_svr, request_vote);
      handler.process(client);
      // agregar reply
  } else {
      Serial.println(F("Unknown RPC type"));
  }
  client.stop();
  raft_svr.dump();
}

void Router::listen(WiFiClient& client, char buff[REQUEST_BUFFER])
{
  uint8_t pos = 0;

  while (client.connected() && pos < REQUEST_BUFFER) {
    if(!client.available()) continue;

    char c = client.read();
    //Serial.print(c);
    buff[pos++] = c;

    if (c == RPC_DELIMITER) {
      buff[pos] = '\0';
      break;
    }
  }
  // Serial.println(" rx");
}

uint8_t Router::rpc_type(JsonObject json)
{
  return (uint8_t)json[RPC_TYPE];
}
