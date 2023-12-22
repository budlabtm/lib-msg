#include "record.h"

#include <cctype>
#include <stdexcept>
#include <string>
#include <vector>

using namespace budlab::lib::msg;

static void validate(Record *record) {
  if (record->topic.empty() || record->message.empty())
    throw std::runtime_error("Topic and Message must to be non-empty.");

  if (record->topic.find('|') != std::string::npos ||
      record->message.find('|') != std::string::npos ||
      record->key.find('|') != std::string::npos)
    throw std::runtime_error("Tokens must not contains '|'.");
}

Record::Record(const std::string &topic_, const std::string &message_,
               const unsigned time_)
    : topic(topic_), message(message_), time(time_) {
  validate(this);
}

Record::Record(const std::string &topic_, const std::string &key_,
               const std::string &message_, const unsigned time_)
    : topic(topic_), key(key_), message(message_), time(time_) {
  validate(this);
}

std::string Record::ToString() {
  std::string record = topic;
  if (!key.empty()) record += "|" + key;
  record += "|" + message;
  if (time != 0) record += "|" + std::to_string(time);

  return record;
}

static std::vector<std::string> split(const std::string &str) {
  std::string s = str;
  std::vector<std::string> r;

  for (decltype(s.size()) i = s.find('|'); i != std::string::npos;
       i = s.find('|')) {
    std::string sub = s.substr(0, i);
    if (!sub.empty()) r.push_back(sub);
    s.erase(0, i + 1);
  }

  if (!s.empty()) r.push_back(s);
  return r;
}

static bool isnumber(const std::string &str) {
  bool r = true;

  for (auto &c : str)
    if (!std::isdigit(c)) {
      r = false;
      break;
    }

  return r;
}

Record Record::FromString(const std::string &str) {
  std::vector<std::string> tokens = split(str);

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
          str);
  }
}