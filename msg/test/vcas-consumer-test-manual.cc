#include <glog/logging.h>
#include <QtCore/QCoreApplication>

#include "msg/consumer.h"
#include "msg/vcas/vcas-client.h"
#include "msg/test/message-handler.h"

using namespace budlab::msg;

int main(int argc, char **argv) {
  FLAGS_logtostderr = 1;
  google::InitGoogleLogging(argv[0]);

  QCoreApplication app(argc, argv);
  VcasClient client;
  Consumer consumer(&client);
  MessageHandler handler(&consumer);

  client.Configure(Credentials("172.16.1.110", 20041));
  consumer.Subscribe("VEPP/CCD/1M1L/x");

  return app.exec();
}