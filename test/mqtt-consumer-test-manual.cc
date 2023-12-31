#include <glog/logging.h>
#include <QtCore/QCoreApplication>

#include "msg/consumer.h"
#include "msg/mqtt/mqtt-client.h"
#include "test/message-handler.h"

using namespace budlab::msg;

int main(int argc, char **argv) {
  FLAGS_logtostderr = 1;
  google::InitGoogleLogging(argv[0]);

  QCoreApplication app(argc, argv);
  MqttClient client;
  Consumer consumer(&client);
  MessageHandler handler(&consumer);

  client.Configure(Credentials("localhost", "hfr-v-client", "mxlinux"));
  consumer.Subscribe("/test");

  return app.exec();
}