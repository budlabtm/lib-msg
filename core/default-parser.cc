#include <stdexcept>
#include <vector>

#include "parser.h"

using std::string;
using std::unordered_map;
using std::vector;

vector<string> budlab::lib::split(const string &str, char sep) {
  string local = str;
  vector<string> r;

  for (std::size_t i = local.find(sep); i != string::npos;
       i = local.find(sep)) {
    string sub = local.substr(0, i);
    if (!sub.empty()) r.push_back(sub);
    local.erase(0, i + 1);
  }

  if (!local.empty()) r.push_back(local);
  return r;
}

bool budlab::lib::isnumber(const std::string &str) {
  bool r = true;

  for (auto &c : str)
    if (!std::isdigit(c)) {
      r = false;
      break;
    }

  return r;
}

unordered_map<string, string> budlab::lib::map(const string &srecord, char os,
                                               char is) {
  unordered_map<string, string> r;
  auto parts = split(srecord, os);

  for (auto &part : parts) {
    auto t = split(part, is);
    if (t.size() == 2) r.insert_or_assign(t[0], t[1]);
  }

  return r;
}

using namespace budlab::lib::msg;

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
          "Parsing error: string must to follow "
          "\"string|[string|]string[|unsigned]\" pattern, but \"" +
          srecord + "\" given.");
  }
}

std::string DefaultParser::ToString(const Record &record) {
  std::string srecord = record.topic + "|";

  if (!record.key.empty()) srecord += record.key + "|";
  srecord += record.message;
  if (record.time != 0) srecord += "|" + std::to_string(record.time);

  return srecord;
}