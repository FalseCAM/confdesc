
#include <gmock/gmock.h>
#include <confdesc/configitem.h>
#include <confdesc/confdesc.h>

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


TEST_F(confdesc_test, ConfDescTest)
{
    std::string json = "{"
    "\"confdesc\":["
    "{\"name\":\"testname\", \"type\":\"integer\",\"value\":15, \"max\":42},"
            "{\"name\":\"testname2\", \"type\":\"float\",\"value\":3.14, \"max\":42}"
      "]"
      "}";

    cd::ConfDesc desc(json);

    for(const auto& items: desc){
        cd::ConfigItem item = items.second;
        EXPECT_EQ((long) 0, item.getMin());
    }
}

