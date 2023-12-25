#include <gtest/gtest.h>

#include <stdexcept>

#include "core/parser.h"
#include "core/record.h"

using namespace budlab::lib::msg;

class DefaultParserTest : public testing::Test {
 protected:
  DefaultParser parser;
};

TEST_F(DefaultParserTest, ToString) {
  EXPECT_EQ("topic|message", parser.ToString(Record("topic", "message")));
  EXPECT_EQ("topic|key|message",
            parser.ToString(Record("topic", "key", "message")));
  EXPECT_EQ("topic|message|123",
            parser.ToString(Record("topic", "message", 123)));
  EXPECT_EQ("topic|key|message|123",
            parser.ToString(Record("topic", "key", "message", 123)));
}

TEST_F(DefaultParserTest, FromString) {
  Record record1 = parser.FromString("topic|message");
  EXPECT_EQ("topic", record1.topic);
  EXPECT_EQ("message", record1.message);

  Record record2 = parser.FromString("topic|message|123");
  EXPECT_EQ("topic", record2.topic);
  EXPECT_EQ("message", record2.message);
  EXPECT_EQ(123, record2.time);

  Record record3 = parser.FromString("topic|key|message");
  EXPECT_EQ("topic", record3.topic);
  EXPECT_EQ("message", record3.message);
  EXPECT_EQ("key", record3.key);

  Record record4 = parser.FromString("topic|key|message|123");
  EXPECT_EQ("topic", record4.topic);
  EXPECT_EQ("message", record4.message);
  EXPECT_EQ("key", record4.key);
  EXPECT_EQ(123, record4.time);

  EXPECT_THROW({ parser.FromString("topic"); }, std::runtime_error);
  EXPECT_THROW({ parser.FromString("first|second|third|fourth|fifth"); },
               std::runtime_error);
  EXPECT_THROW({ parser.FromString("topic|key|message|number"); },
               std::runtime_error);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}