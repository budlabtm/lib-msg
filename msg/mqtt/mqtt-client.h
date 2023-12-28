#ifndef LIB_MSG_MQTT_CLIENT_H
#define LIB_MSG_MQTT_CLIENT_H

#include <QtCore/QObject>
#include <mqtt/async_client.h>

#include "msg/client.h"

namespace budlab::msg {

class MqttClient : public QObject, public IClient, private mqtt::callback {
  Q_OBJECT

 private:
  std::unique_ptr<mqtt::async_client> client_ = nullptr;

 public:
  MqttClient(IParser *parser = nullptr);
  ~MqttClient();

  void Configure(const Credentials &c) override;
  void Send(const Record &record) override;
  void Subscribe(const std::string &topic) override;
  void Unsubscribe(const std::string &topic) override;
  bool IsConnected() override;

  // Callback
  void connected(const std::string &cause) override;
  void connection_lost(const std::string &cause) override;
  void message_arrived(mqtt::const_message_ptr msg) override;

 signals:
  void Consumed(Record record) override;
  void Connected() override;
  void Disconnected() override;
};

}  // namespace budlab::msg

#endif  // LIB_MSG_MQTT_CLIENT_H
