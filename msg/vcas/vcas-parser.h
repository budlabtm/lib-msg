#ifndef LIB_MSG_VCAS_PARSER_H
#define LIB_MSG_VCAS_PARSER_H

#include "msg/parser.h"

#define TIME_FORMAT "dd.MM.yyyy HH_mm_ss.zzz"

namespace budlab::msg {

class VcasParser : public IParser {
 public:
  const std::string kFormat = "name:{string}|time:{" TIME_FORMAT "}|val:{string}";
  Record FromString(const std::string &srecord);
  std::string ToString(const Record &record);
};

}  // namespace budlab::msg

#endif  // LIB_MSG_VCAS_PARSER_H
