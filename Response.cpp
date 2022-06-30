#include "Constants.hpp"
#include "Response.hpp"
#include "RPC.hpp"

using namespace locke;

Response::Response (char msg[RESPONSE_BUFFER])  
{
}

Response::Response (bool success,
                    uint32_t term,
                    RPC::Type type)
{
  doc[RPC_TYPE]    = (uint8_t)type;
  doc[RPC_TERM]    = term;
  doc[RPC_SUCCESS] = success;
 }

uint32_t Response::term() const
{
  return doc[RPC_TERM];
}

bool Response::success() const
{
  return doc[RPC_SUCCESS];
}

uint8_t Response::type() const
{
  return (uint8_t)doc[RPC_TYPE];
}

void Response::print()
{
  serializeJson(doc,Serial);
}

void Response::send(WiFiClient client) 
{
  serializeJson(doc,client);
}
