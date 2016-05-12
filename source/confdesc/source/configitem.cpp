#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <confdesc/configitem.h>

namespace cd {

ConfigItem::ConfigItem(std::string json) {
  this->json = json;
  parse();
}

void ConfigItem::parse() {
  boost::property_tree::ptree ptconfig;
  std::stringstream ssconfig(json);
  boost::property_tree::read_json(ssconfig, ptconfig);

  if (ptconfig.get_optional<std::string>("name")) {
    this->name = ptconfig.get<std::string>("name");
  }

  if (ptconfig.get_optional<std::string>("type")) {
    this->type = cd::dataTypeFromString(ptconfig.get<std::string>("type"));
  }

  if (ptconfig.get_optional<long>("min")) {
    this->min = ptconfig.get<long>("min");
  }

  if (ptconfig.get_optional<long>("max")) {
    this->max = ptconfig.get<long>("max");
  }

  parseValue();
}

void ConfigItem::parseValue() {
    boost::property_tree::ptree ptconfig;
    std::stringstream ssconfig(json);
    boost::property_tree::read_json(ssconfig, ptconfig);
  if (type == cd::DataType::BOOLEAN) {
    if (ptconfig.get_optional<bool>("value")) {
      this->boolValue = ptconfig.get<bool>("value");
    }
  } else if (type == cd::DataType::INTEGER) {
    if (ptconfig.get_optional<long>("value")) {
      this->intValue = ptconfig.get<long>("value");
    }
  } else if (type == cd::DataType::FLOAT) {
    if (ptconfig.get_optional<double>("value")) {
      this->floatValue = ptconfig.get<double>("value");
    }
  } else if (type == cd::DataType::STRING) {
    if (ptconfig.get_optional<std::string>("value")) {
      this->strValue = ptconfig.get<std::string>("value");
    }
  }
}

std::string ConfigItem::getType() { return cd::dataTypeToString(type); }

std::string ConfigItem::getName() { return name; }

long ConfigItem::getMin() { return min; }

long ConfigItem::getMax() { return max; }

template <> long ConfigItem::getValue<long>(){ return intValue; }
template <> int ConfigItem::getValue<int>(){ return intValue; }
template <> bool ConfigItem::getValue<bool>(){ return boolValue; }
template <> float ConfigItem::getValue<float>(){ return floatValue; }
template <> double ConfigItem::getValue<double>(){ return floatValue; }
template <> std::string ConfigItem::getValue<std::string>(){ return strValue; }

}
