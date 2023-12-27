#include <stdexcept>
#include <vector>

#include "msg/parser.h"

using namespace budlab::msg;
using namespace std;

vector<string> budlab::split(const string &str, char sep) {
  string local = str;
  vector<string> r;

  for (size_t i = local.find(sep); i != string::npos; i = local.find(sep)) {
    string sub = local.substr(0, i);
    if (!sub.empty()) r.push_back(sub);
    local.erase(0, i + 1);
  }

  if (!local.empty()) r.push_back(local);
  return r;
}

bool budlab::isnumber(const string &str) {
  bool r = true;

  for (auto &c : str)
    if (!isdigit(c)) {
      r = false;
      break;
    }

  return r;
}

unordered_map<string, string> budlab::map(const string &srecord, char os,
                                          char is) {
  unordered_map<string, string> r;
  auto parts = split(srecord, os);

  for (auto &part : parts) {
    auto t = split(part, is);
    if (t.size() == 2) r.insert_or_assign(t[0], t[1]);
  }

  return r;
}

Record DefaultParser::FromString(const string &srecord) {
  vector<string> tokens = split(srecord, '|');

  switch (tokens.size()) {
    case 2:
      return Record(tokens[0], tokens[1]);
    case 3:
      if (isnumber(tokens[2]))
        return Record(tokens[0], tokens[1], stoul(tokens[2]));
      else
        return Record(tokens[0], tokens[1], tokens[2]);
    case 4:
      if (isnumber(tokens[3]))
        return Record(tokens[0], tokens[1], tokens[2], stoul(tokens[3]));
    default:
      throw runtime_error("Format error - \"" + kFormat +
                          "\" expected, but \"" + srecord + "\" were given");
  }
}

string DefaultParser::ToString(const Record &record) {
  string srecord = record.topic + "|";

  if (!record.key.empty()) srecord += record.key + "|";
  srecord += record.message;
  if (record.time != 0) srecord += "|" + to_string(record.time);

  return srecord;
}
