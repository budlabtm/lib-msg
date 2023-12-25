#include "vcas-client.h"

#include <iostream>

using namespace budlab::lib::msg;

void VcasClient::Send(const std::string &record) {
  QTextStream out(socket_);
  out << QString::fromStdString(record);
}

VcasClient::VcasClient(IParser *parser) : IClient(parser) {
  timer_ = new QTimer(this);
  socket_ = new QTcpSocket(this);

  timer_->setInterval(2000);

  connect(socket_, SIGNAL(connected()), SLOT(OnConnected()));
  connect(socket_, SIGNAL(disconnected()), SLOT(OnDisconnected()));
  connect(socket_, SIGNAL(readyRead()), SLOT(OnReadyRead()));
  connect(timer_, SIGNAL(timeout()), SLOT(OnReconnectTimeout()));
}

VcasClient::~VcasClient() {
  if (socket_->isValid()) socket_->disconnectFromHost();

  delete timer_;
  delete socket_;
}

void VcasClient::Configure(const Credentials &c) {
  host_ = c.host;
  port_ = c.port;

  timer_->start();
}

void VcasClient::Send(const Record &record) {
  if (!socket_->isValid()) return;
  Send(parser_->ToString(record));
}

void VcasClient::Subscribe(const std::string &topic) {
  subscribed_.insert(topic);

  if (socket_->isValid()) Send("name:" + topic + "|method:subscr");
}

void VcasClient::Unsubscribe(const std::string &topic) {
  subscribed_.extract(topic);

  if (subscribed_.count(topic) == 0)
    Send("name:" + topic + "|method:release\n");
}

bool VcasClient::IsConnected() { return socket_->isValid(); }

void VcasClient::OnReadyRead() {
  while (socket_->canReadLine()) {
    std::string line = tr(socket_->readLine()).remove('\n').toStdString();
    std::cout << line << std::endl;
    // emit Consumed(parser_->FromString(line));
  }
}

void VcasClient::OnConnected() {
  timer_->stop();

  for (auto &t : subscribed_) Send("name:" + t + "|method:subscr\n");

  std::cout << "Connected" << std::endl;
  emit Connected();
}

void VcasClient::OnDisconnected() {
  timer_->start();
  std::cout << "Disconnected" << std::endl;
  emit Disconnected();
}

void VcasClient::OnReconnectTimeout() {
  socket_->connectToHost(QString::fromStdString(host_), port_);
}