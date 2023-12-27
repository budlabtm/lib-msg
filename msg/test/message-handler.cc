#include "msg/test/message-handler.h"

#include <iostream>

using namespace budlab::msg;
using std::cout;
using std::endl;

MessageHandler::MessageHandler(Consumer *consumer) : consumer_(consumer) {
  connect(consumer_, SIGNAL(Consumed(Record)), this, SLOT(OnConsumed(Record)));
}

void MessageHandler::OnConsumed(Record record) {
  cout << "Income:\n\tFrom: \"" + record.topic +
              "\"\n\tMessage: " + record.message +
              "\n\tAt: " + std::to_string(record.time)
       << endl;
}