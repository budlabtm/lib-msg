#include "msg/record.h"

#include <stdexcept>
#include <string>

using namespace budlab::msg;
using namespace std;

static void validate(Record *record) {
  if (record->topic.empty() || record->message.empty())
    throw runtime_error("Topic and Message must to be non-empty.");

  if (record->topic.find('|') != string::npos ||
      record->message.find('|') != string::npos ||
      record->key.find('|') != string::npos)
    throw runtime_error("Tokens must not contain '|'.");
}

Record::Record(const string &topic_, const string &message_,
               const unsigned long time_)
    : topic(topic_), message(message_), time(time_) {
  validate(this);
}

Record::Record(const string &topic_, const string &key_, const string &message_,
               const unsigned long time_)
    : topic(topic_), key(key_), message(message_), time(time_) {
  validate(this);
}
