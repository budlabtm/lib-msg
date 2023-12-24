#ifndef LIB_MSG_CLIENT_H
#define LIB_MSG_CLIENT_H

#include <string>
#include <unordered_set>

#include "QtCore/QObject"
#include "record.h"

namespace budlab::lib::msg {

struct Credentials {
  std::string host;
  std::string username;
  std::string password;

  Credentials(const std::string &host_) : host(host_) {}
  Credentials(const std::string &host_, const std::string &username_,
              const std::string &password_)
      : host(host_), username(username_), password(password_) {}
};

class IClient {
protected:
  std::unordered_multiset<std::string> subscribed_;

public:
  virtual ~IClient() {}

  virtual void Configure(const Credentials &c) = 0;
  virtual void Send(const Record &record) = 0;
  virtual void Subscribe(const std::string &topic) = 0;
  virtual void Unsubscribe(const std::string &topic) = 0;
  virtual bool IsConnected() = 0;

signals: // Qt only
  virtual void Consumed(Record record){};
  virtual void Connected(){};
  virtual void Disconnected(){};
};

} // namespace budlab::lib::msg

#endif // LIB_MSG_CLIENT_H