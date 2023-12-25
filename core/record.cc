#include "record.h"

#include <stdexcept>
#include <string>

using namespace budlab::lib::msg;

static void validate(Record *record) {
  if (record->topic.empty() || record->message.empty())
    throw std::runtime_error("Topic and Message must to be non-empty.");

  if (record->topic.find('|') != std::string::npos ||
      record->message.find('|') != std::string::npos ||
      record->key.find('|') != std::string::npos)
    throw std::runtime_error("Tokens must not contains '|'.");
}

Record::Record(const std::string &topic_, const std::string &message_,
               const unsigned time_)
    : topic(topic_), message(message_), time(time_) {
  validate(this);
}

Record::Record(const std::string &topic_, const std::string &key_,
               const std::string &message_, const unsigned time_)
    : topic(topic_), key(key_), message(message_), time(time_) {
  validate(this);
}
