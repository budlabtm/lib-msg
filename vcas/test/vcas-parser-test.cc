#include "vcas/vcas-parser.h"

#include <gtest/gtest.h>

using namespace budlab::lib::msg;

class VcasParserTest : public testing::Test {
 protected:
  VcasParser parser;
};

TEST_F(VcasParserTest, ToString) {
  EXPECT_EQ("name:topic|time:24.12.2023 16_30_30.191|val:payload",
            parser.ToString(Record("topic", "payload", 1703410230191)));
  EXPECT_EQ("name:topic|time:24.12.2023 16_30_30.191|val:-191",
            parser.ToString(Record("topic", "-191", 1703410230191)));
}

TEST_F(VcasParserTest, FromString) {
  Record r =
      parser.FromString("name:topic|time:24.12.2023 16_30_30.191|val:payload");

  EXPECT_EQ("topic", r.topic);
  EXPECT_EQ("payload", r.message);
  EXPECT_EQ(1703410230191, r.time);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}