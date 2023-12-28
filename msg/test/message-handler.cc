#include <iostream>

#include "msg/test/message-handler.h"

using namespace budlab::msg;
using namespace std;

MessageHandler::MessageHandler(Consumer *consumer) : consumer_(consumer) {
  connect(consumer_, SIGNAL(Consumed(Record)), this, SLOT(OnConsumed(Record)));
}

void MessageHandler::OnConsumed(Record record) {
  cout << "Income:\n\tFrom: " + record.topic + "\n\tKey: " + record.key +
              "\n\tMessage: " + record.message +
              "\n\tAt: " + std::to_string(record.time)
       << endl;
}