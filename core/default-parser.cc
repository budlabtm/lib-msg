#include <vector>

#include "parser.h"
#include "stdexcept"

using namespace budlab::lib::msg;

static bool isnumber(const std::string &str) {
  bool r = true;

  for (auto &c : str)
    if (!std::isdigit(c)) {
      r = false;
      break;
    }

  return r;
}

Record DefaultParser::FromString(const std::string &srecord) {
  std::vector<std::string> tokens = split(srecord, '|');

  switch (tokens.size()) {
    case 2:
      return Record(tokens[0], tokens[1]);
    case 3:
      if (isnumber(tokens[2]))
        return Record(tokens[0], tokens[1], std::stoul(tokens[2]));
      else
        return Record(tokens[0], tokens[1], tokens[2]);
    case 4:
      if (isnumber(tokens[3]))
        return Record(tokens[0], tokens[1], tokens[2], std::stoul(tokens[3]));
    default:
      throw std::runtime_error(
          "Message pattern must be \"string|[string|]string[|unsigned]\", "
          "but: " +
          srecord);
  }
}

std::string DefaultParser::ToString(const Record &record) {
  std::string srecord = record.topic + "|";

  if (!record.key.empty()) srecord += record.key + "|";
  srecord += record.message;
  if (record.time != 0) srecord += "|" + std::to_string(record.time);

  return srecord;
}