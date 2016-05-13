
#include <gmock/gmock.h>
#include <confdesc/configitem.h>

class confdesc_test: public testing::Test
{
public:
};

TEST_F(confdesc_test, ConfigItemTest)
{
    std::string json = "{\"name\":\"testname\", \"type\":\"integer\",\"value\":15, \"max\":42}";
    cd::ConfigItem ci(json);
    EXPECT_EQ((std::string) "testname", ci.getName());
    EXPECT_EQ((std::string) "integer", ci.getTypeAsString());
    EXPECT_EQ(cd::DataType::INTEGER, ci.getType());
    EXPECT_EQ((long) 15, ci.getValue<long>());
    EXPECT_EQ((long) 42, ci.getMax());
    EXPECT_EQ((long) 0, ci.getMin());
}

