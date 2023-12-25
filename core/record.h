#ifndef LIB_MSG_RECORD_H
#define LIB_MSG_RECORD_H

#include <string>

namespace budlab::lib::msg {

struct ParseResult {
  std::string topic;
  std::string payload;
};

struct Record {
  std::string topic;
  std::string key;
  std::string message;
  unsigned time;

  Record(const std::string &topic_, const std::string &message_,
         const unsigned time_ = 0);

  Record(const std::string &topic_, const std::string &key_,
         const std::string &message_, const unsigned time_ = 0);
};

}  // namespace budlab::lib::msg

#endif  // LIB_MSG_RECORD_H