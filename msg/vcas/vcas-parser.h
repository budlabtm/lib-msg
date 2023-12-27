#ifndef LIB_MSG_VCAS_PARSER_H
#define LIB_MSG_VCAS_PARSER_H

#include "msg/parser.h"

namespace budlab::msg {

class VcasParser : public IParser {
 public:
  Record FromString(const std::string &srecord);
  std::string ToString(const Record &record);
};

}  // namespace budlab::msg

#endif  // LIB_MSG_VCAS_PARSER_H
