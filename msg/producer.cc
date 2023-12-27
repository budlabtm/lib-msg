#include "msg/producer.h"

using namespace budlab::msg;

Producer::Producer(IClient *client) { client_.reset(client); }

bool Producer::Send(const Record &record) {
  if (!client_->IsConnected()) return false;

  client_->Send(record);
  return true;
}