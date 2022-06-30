#include "SyncRequest.hpp"
#include "Response.hpp"

using namespace locke;

bool SyncRequest::perform(IPAddress& ip, JsonObject json, Result* res)
{
  WiFiClient client;
  StaticJsonDocument<JSON_SMALL> doc;
  char buff[RESPONSE_BUFFER];
  uint8_t pos = 0;

  if (!client.connect(ip, RAFT_PORT)) {
    return false;
  }

  serializeJson(json, client);

  while (client.connected() && pos < RESPONSE_BUFFER) {
    if (!client.available()) continue;

    char c = client.read();
    buff[pos++] = c;

    if (c == RPC_DELIMITER) {
      buff[pos] = '\0';
      break;
    }
  }

  client.stop();

  Response response(buff);
  res->success = response.success();
  res->term = response.term();

  return true;
}
