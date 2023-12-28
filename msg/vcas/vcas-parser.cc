#include "msg/vcas/vcas-parser.h"

#include <QtCore/QDateTime>
#include <unordered_map>

using namespace budlab::msg;
using namespace std;

Record VcasParser::FromString(const string &srecord) {
  unordered_map<string, string> tokens = map(srecord, '|', ':');

  if (tokens.size() < 3 || !tokens.count("name") || !tokens.count("time") ||
      !tokens.count("val"))
    throw runtime_error("Format error - \"" + kFormat + "\" expected, but \"" +
                        srecord + "\" were given");

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