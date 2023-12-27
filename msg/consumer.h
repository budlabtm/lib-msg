#ifndef LIB_MSG_CONSUMER_H
#define LIB_MSG_CONSUMER_H

#include <QtCore/QObject>
#include <memory>
#include <string>
#include <unordered_map>

#include "msg/client.h"
#include "msg/record.h"

namespace budlab::msg {

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

}  // namespace budlab::msg

#endif  // LIB_MSG_CONSUMER_H