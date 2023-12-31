#ifndef LIB_MSG_CLIENT_H
#define LIB_MSG_CLIENT_H

#include <QtCore/QObject>
#include <string>
#include <unordered_set>

#include "msg/parser.h"
#include "msg/record.h"

namespace budlab::msg {

struct Credentials {
  std::string host;
  std::string username;
  std::string password;
  unsigned port;

  Credentials(const std::string &host_, unsigned port_ = 1883)
      : host(host_), port(port_) {}

  Credentials(const std::string &host_, const std::string &username_,
              const std::string &password_, unsigned port_ = 1883)
      : host(host_), username(username_), password(password_), port(port_) {}
};

class IClient {
 protected:
  std::unordered_multiset<std::string> subscribed_;
  std::shared_ptr<IParser> parser_;

 public:
  IClient(IParser *parser = nullptr) {
    if (parser == nullptr)
      parser_.reset(new DefaultParser());
    else
      parser_.reset(parser);
  }

  virtual ~IClient() {}

  virtual void Configure(const Credentials &c) = 0;
  virtual void Send(const Record &record) = 0;
  virtual void Subscribe(const std::string &topic) = 0;
  virtual void Unsubscribe(const std::string &topic) = 0;
  virtual bool IsConnected() = 0;

  // Signals
  virtual void Consumed(Record record) = 0;
  virtual void Connected() = 0;
  virtual void Disconnected() = 0;
};

}  // namespace budlab::msg

#endif  // LIB_MSG_CLIENT_H