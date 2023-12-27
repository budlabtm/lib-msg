#ifndef LIB_MSG_RECORD_H
#define LIB_MSG_RECORD_H

#include <string>

namespace budlab::msg {

struct ParseResult {
  std::string topic;
  std::string payload;
};

struct Record {
  std::string topic;
  std::string key;
  std::string message;
  unsigned long time;

  Record(const std::string &topic_, const std::string &message_,
         const unsigned long time_ = 0);

  Record(const std::string &topic_, const std::string &key_,
         const std::string &message_, const unsigned long time_ = 0);
};

}  // namespace budlab::msg

#endif  // LIB_MSG_RECORD_H