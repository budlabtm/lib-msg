#ifndef LIB_MSG_PARSER_H
#define LIB_MSG_PARSER_H

#include <string>
#include <vector>

#include "record.h"

namespace budlab::lib::msg {

std::vector<std::string> split(const std::string &str, char sep) {
  std::string s = str;
  std::vector<std::string> r;

  for (decltype(s.size()) i = s.find(sep); i != std::string::npos;
       i = s.find(sep)) {
    std::string sub = s.substr(0, i);
    if (!sub.empty()) r.push_back(sub);
    s.erase(0, i + 1);
  }

  if (!s.empty()) r.push_back(s);
  return r;
}

class IParser {
 public:
  virtual Record FromString(const std::string &srecord) = 0;
  virtual std::string ToString(const Record &record) = 0;
};

class DefaultParser : public IParser {
 public:
  Record FromString(const std::string &srecord);
  std::string ToString(const Record &record);
};

}  // namespace budlab::lib::msg

#endif  // LIB_MSG_RECORD_H