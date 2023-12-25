#ifndef LIB_MSG_PARSER_H
#define LIB_MSG_PARSER_H

#include <string>
#include <unordered_map>
#include <vector>

#include "record.h"

namespace budlab::lib {

std::vector<std::string> split(const std::string &str, char sep = '|');
bool isnumber(const std::string &str);
std::unordered_map<std::string, std::string> map(const std::string &srecord,
                                                 char os = '|', char is = ':');

namespace msg {

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

}  // namespace msg

}  // namespace budlab::lib

#endif  // LIB_MSG_RECORD_H