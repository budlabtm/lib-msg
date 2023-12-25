#ifndef LIB_MSG_VCAS_PARSER_H
#define LIB_MSG_VCAS_PARSER_H

#include "core/parser.h"

namespace budlab::lib::msg {

class VcasParser : public IParser {
 public:
  Record FromString(const std::string &srecord);
  std::string ToString(const Record &record);
};

}  // namespace budlab::lib::msg

#endif  // LIB_MSG_VCAS_CLIENT_H
