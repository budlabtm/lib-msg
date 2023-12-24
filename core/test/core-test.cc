#include <stdexcept>

#include "core/record.h"
#include "gtest/gtest.h"

// Test
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

using namespace budlab::lib::msg;

TEST(Record, Construct) {
  Record record1("topic", "message");
  EXPECT_EQ(record1.message, "message");
  EXPECT_THROW({ Record record2("", ""); }, std::runtime_error);
  EXPECT_THROW({ Record record3("top|ic", "message"); }, std::runtime_error);
}

TEST(Record, Split) {
  std::vector<std::string> r = split("russia|usa|norway|canada");
  EXPECT_EQ(4, r.size());

  r = split("|usa|norway|canada");
  EXPECT_EQ(3, r.size());

  r = split("russia|usa|norway|");
  EXPECT_EQ(3, r.size());

  r = split("|usa|norway|");
  EXPECT_EQ(2, r.size());
}

TEST(Record, ToString) {
  Record record1("topic", "message");
  EXPECT_EQ("topic|message", record1.ToString());

  Record record2("topic", "key", "message");
  EXPECT_EQ("topic|key|message", record2.ToString());

  Record record3("topic", "message", 123);
  EXPECT_EQ("topic|message|123", record3.ToString());

  Record record4("topic", "key", "message", 123);
  EXPECT_EQ("topic|key|message|123", record4.ToString());
}

TEST(Record, FromString) {
  Record record1 = Record::FromString("topic|message");
  EXPECT_EQ("topic", record1.topic);
  EXPECT_EQ("message", record1.message);

  Record record2 = Record::FromString("topic|message|123");
  EXPECT_EQ("topic", record2.topic);
  EXPECT_EQ("message", record2.message);
  EXPECT_EQ(123, record2.time);

  Record record3 = Record::FromString("topic|key|message");
  EXPECT_EQ("topic", record3.topic);
  EXPECT_EQ("message", record3.message);
  EXPECT_EQ("key", record3.key);

  Record record4 = Record::FromString("topic|key|message|123");
  EXPECT_EQ("topic", record4.topic);
  EXPECT_EQ("message", record4.message);
  EXPECT_EQ("key", record4.key);
  EXPECT_EQ(123, record4.time);

  EXPECT_THROW({ Record::FromString("topic"); }, std::runtime_error);
  EXPECT_THROW({ Record::FromString("first|second|third|fourth|fifth"); },
               std::runtime_error);
  EXPECT_THROW({ Record::FromString("topic|key|message|number"); },
               std::runtime_error);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}