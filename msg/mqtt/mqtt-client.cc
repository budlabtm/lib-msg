#include "mqtt-client.h"

#include <glog/logging.h>

#include <iostream>

using namespace budlab::msg;
using std::string;

MqttClient::MqttClient(IParser *parser) : IClient(parser) {}

MqttClient::~MqttClient() {
  if (IsConnected()) client_->disconnect();
}

void MqttClient::Configure(const Credentials &c) {
  std::cout << "Connecting..." << std::endl;
  mqtt::connect_options opts(c.username, c.password);

  client_.reset(new mqtt::async_client(c.host, "client"));
  client_->set_callback(*this);
  opts.set_automatic_reconnect(true);
  client_->connect(opts);
}

void MqttClient::Send(const Record &record) {
  if (IsConnected()) client_->publish(record.topic, parser_->ToString(record));
}

void MqttClient::Subscribe(const std::string &topic) {
  subscribed_.insert(topic);
  if (IsConnected()) client_->subscribe(topic, 1);
}

void MqttClient::Unsubscribe(const std::string &topic) {
  subscribed_.extract(topic);
  if (subscribed_.count(topic) == 0 && IsConnected())
    client_->unsubscribe(topic);
}

bool MqttClient::IsConnected() {
  return client_ != nullptr && client_->is_connected();
}

void MqttClient::connected(const std::string &cause) {
  std::cout << "Connected" << std::endl;
  for (auto &topic : subscribed_) client_->subscribe(topic, 1);
  emit Connected();
}

void MqttClient::connection_lost(const std::string &cause) {
  std::cout << "Disconnected" << std::endl;
  emit Disconnected();
}

void MqttClient::message_arrived(mqtt::const_message_ptr msg) {
  try {
    emit Consumed(parser_->FromString(msg->get_payload_str()));
  } catch (const std::runtime_error &err) {
    LOG(ERROR) << "LIB_MSG_MQTT_CLIENT: " << err.what();
  }
}
