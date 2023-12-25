#include "vcas/vcas-client.h"

#include <QtCore/QCoreApplication>

#include "core/consumer.h"

using namespace budlab::lib::msg;

int main(int argc, char **argv) {
  QCoreApplication app(argc, argv);
  VcasClient client();

  client.Configure(Credentials("172.16.1.110", 20041));

  client.Subscribe("VEPP/CCD/1M1L/x");

  return app.exec();
}