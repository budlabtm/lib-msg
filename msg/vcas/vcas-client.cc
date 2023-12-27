#include "msg/vcas/vcas-client.h"

#include <glog/logging.h>

#include <iostream>

#include "msg/vcas/vcas-parser.h"

using namespace budlab::msg;

void VcasClient::Send(const std::string &record) {
  QTextStream out(socket_);
  out << QString::fromStdString(record);
}

VcasClient::VcasClient(IParser *parser) : IClient(parser) {
  if (parser == nullptr) parser_.reset(new VcasParser());

  timer_ = new QTimer(this);
  socket_ = new QTcpSocket(this);

  timer_->setInterval(2000);

  connect(socket_, SIGNAL(connected()), SLOT(OnConnected()));
  connect(socket_, SIGNAL(disconnected()), SLOT(OnDisconnected()));
  connect(socket_, SIGNAL(readyRead()), SLOT(OnReadyRead()));
  connect(timer_, SIGNAL(timeout()), SLOT(OnReconnectTimeout()));
}

VcasClient::~VcasClient() {
  if (IsConnected()) socket_->disconnectFromHost();

  delete timer_;
  delete socket_;
}

void VcasClient::Configure(const Credentials &c) {
  host_ = c.host;
  port_ = c.port;

  timer_->start();
}

void VcasClient::Send(const Record &record) {
  if (!IsConnected()) return;
  Send(parser_->ToString(record));
}

void VcasClient::Subscribe(const std::string &topic) {
  subscribed_.insert(topic);

  if (IsConnected()) Send("name:" + topic + "|method:subscr");
}

void VcasClient::Unsubscribe(const std::string &topic) {
  subscribed_.extract(topic);

  if (subscribed_.count(topic) == 0 && IsConnected())
    Send("name:" + topic + "|method:release\n");
}

bool VcasClient::IsConnected() { return socket_->isValid(); }

void VcasClient::OnReadyRead() {
  while (socket_->canReadLine()) {
    std::string line = tr(socket_->readLine()).remove('\n').toStdString();
    try {
      emit Consumed(parser_->FromString(line));
    } catch (const std::runtime_error &err) {
      LOG(ERROR) << "LIB_MSG_VCAS_CLIENT: " << err.what();
    }
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