#ifndef LIB_MSG_VCAS_CLIENT_H
#define LIB_MSG_VCAS_CLIENT_H

#include <QtCore/QObject>
#include <QtCore/QTimer>
#include <QtNetwork/QTcpSocket>

#include "core/client.h"

namespace budlab::lib::msg {

class VcasClient : public QObject, public IClient {
  Q_OBJECT

 private:
  QTcpSocket *socket_ = nullptr;
  QTimer *timer_ = nullptr;
  std::string host_;
  unsigned port_;

  void Send(const std::string &record);

 public:
  VcasClient(IParser *parser = nullptr);
  ~VcasClient();

  void Configure(const Credentials &c) override;
  void Send(const Record &record) override;
  void Subscribe(const std::string &topic) override;
  void Unsubscribe(const std::string &topic) override;
  bool IsConnected() override;

 private slots:
  void OnReadyRead();
  void OnConnected();
  void OnDisconnected();

  void OnReconnectTimeout();

 signals:
  void Consumed(Record record) override;
  void Connected() override;
  void Disconnected() override;
};

}  // namespace budlab::lib::msg

#endif  // LIB_MSG_VCAS_CLIENT_H
