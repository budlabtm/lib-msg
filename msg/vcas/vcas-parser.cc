#include "msg/vcas/vcas-parser.h"

#include <QtCore/QDateTime>
#include <unordered_map>

using namespace budlab::msg;
using std::runtime_error;
using std::string;
using std::unordered_map;

#define ERROR_MESSAGE(srecord)                                 \
  "Parsing error: record must follow "                         \
  "\"[...|]name:topic|time:time|val:message[|...]\", but \"" + \
      srecord + "\" were given."

#define TIME_FORMAT "dd.MM.yyyy HH_mm_ss.zzz"

Record VcasParser::FromString(const string &srecord) {
  unordered_map<string, string> tokens = map(srecord, '|', ':');

  if (tokens.size() < 3 || !tokens.count("name") || !tokens.count("time") ||
      !tokens.count("val"))
    throw runtime_error(ERROR_MESSAGE(srecord));

  return Record(
      tokens["name"], tokens["val"],
      QDateTime::fromString(QString::fromStdString(tokens["time"]), TIME_FORMAT)
          .toMSecsSinceEpoch());
}

string VcasParser::ToString(const Record &record) {
  return "name:" + record.topic + "|time:" +
         QDateTime::fromMSecsSinceEpoch(record.time)
             .toString(TIME_FORMAT)
             .toStdString() +
         "|val:" + record.message;
}