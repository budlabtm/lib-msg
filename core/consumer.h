#ifndef LIB_MSG_CONSUMER_H
#define LIB_MSG_CONSUMER_H

#include <memory>
#include <string>
#include <unordered_map>

#include "QtCore/QObject"
#include "client.h"
#include "record.h"

namespace budlab::lib::msg {

class Consumer : public QObject {
  Q_OBJECT

 private:
  std::shared_ptr<IClient> client_;
  std::unordered_map<std::string, std::string> subscribed_;

 public:
  Consumer(IClient *client);
  virtual ~Consumer() {}

  void Subscribe(const std::string &topic);
  void Subscribe(const std::string &topic, const std::string &key);
  void Unsubscribe(const std::string &topic);

 signals:
  void Consumed(Record record);

 private slots:
  void OnConsumed(Record record);
};

}  // namespace budlab::lib::msg

#endif  // LIB_MSG_CONSUMER_H