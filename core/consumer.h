#ifndef LIB_MSG_CONSUMER_H
#define LIB_MSG_CONSUMER_H

#include <memory>
#include <string>
#include <unordered_map>

#include "QtCore/QObject"
#include "client.h"
#include "record.h"

namespace budlab::lib::msg {

class IConsumer {
protected:
  std::shared_ptr<IClient> client_;
  std::unordered_map<std::string, std::string> subscribed_;
  Record (*parser_)(std::string &) = nullptr;

public:
  virtual ~IConsumer() {}

  virtual void Subscribe(const std::string &topic) = 0;
  virtual void Subscribe(const std::string &topic, const std::string &key) = 0;
  virtual void Unsubscribe(const std::string &topic) = 0;

  void SetParser(Record (*parser)(std::string &)) { parser_ = parser; }

signals: // Qt only
  virtual void Consumed(Record record) = 0;

private slots: // Qt only
  virtual void OnConsumed(Record record) = 0;
};

} // namespace budlab::lib::msg

#endif // LIB_MSG_CONSUMER_H