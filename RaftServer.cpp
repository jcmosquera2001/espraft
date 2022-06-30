#include "RaftServer.hpp"
#include "Configuration.hpp"
#include "Log.hpp"

using namespace locke;

RaftServer::RaftServer(char name) :
    current_term(INITIAL_TERM),
    name(name),
    voted_for(NOBODY_YET) {}

void RaftServer::set_status(State status)
{
  _status = status;
}

State RaftServer::get_status()
{
  return _status;
}

void RaftServer::setup()
{
  restore();
  update_election_timeout();
  set_status(Follower);
  Log::setup();
}

void RaftServer::save()
{
  Configuration::save(*this);
}

void RaftServer::restore()
{
  Configuration::restore(*this);
}

void RaftServer::update_election_timeout()
{
  _election_timeout = millis() + ELECTION_TIMEOUT;
}

bool RaftServer::should_become_candidate()
{
  return millis() > _election_timeout;
}

void RaftServer::dump() {
  Serial.println("***********************************");
  Serial.print("Server name:");Serial.println(name);
  Serial.print("current_term:");Serial.println(current_term);
  Serial.print("voted_for:");Serial.println((int)voted_for);
  Serial.print("status:");Serial.println(_status);
  Log::dump();

}