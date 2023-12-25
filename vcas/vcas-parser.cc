#include "vcas-parser.h"

#include <unordered_map>

#include "QtCore/QDateTime"

using namespace budlab::lib::msg;

static std::unordered_map<std::string, std::string> map(
    const std::string &srecord) {
  std::unordered_map<std::string, std::string> r;
  std::vector<std::string> parts = split(srecord, '|');

  for (auto &part : parts) {
    std::vector<std::string> t = split(part, ':');
    r.insert(t[0], t[1]);
  }

  return r;
}

Record VcasParser::FromString(const std::string &srecord) {
  std::unordered_map<std::string, std::string> tokens = map(srecord);
}