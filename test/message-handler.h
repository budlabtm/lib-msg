#ifndef LIB_MSG_MESSAGE_HANDLER_H
#define LIB_MSG_MESSAGE_HANDLER_H

#include <QtCore/QObject>

#include "msg/consumer.h"

namespace budlab::msg {

class MessageHandler : public QObject {
  Q_OBJECT

 private:
  Consumer *consumer_ = nullptr;

 public:
  MessageHandler(Consumer *consumer);
  virtual ~MessageHandler() {}

 public slots:
  void OnConsumed(Record record);
};

}  // namespace budlab::msg

#endif  // LIB_MSG_MESSAGE_HANDLER_H