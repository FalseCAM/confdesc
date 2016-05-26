#include <boost/property_tree/json_parser.hpp>

#include <confdesc/configitem.h>
#include <exception>

namespace cd {

ConfigItem::ConfigItem() {}

ConfigItem::ConfigItem(std::string json) {
  std::stringstream ssconfig(json);
  boost::property_tree::read_json(ssconfig, ptconfig);
}

ConfigItem::ConfigItem(boost::property_tree::ptree ptconfig) {
  this->ptconfig = ptconfig;
}

cd::DataType ConfigItem::getType() {
  if (ptconfig.get_optional<std::string>("type")) {
    return cd::dataTypeFromString(ptconfig.get<std::string>("type"));
  } else {
    throw std::runtime_error("does not contain type");
  }
}

std::string ConfigItem::getTypeAsString() {
  return cd::dataTypeToString(getType());
}

void ConfigItem::setType(std::string type) { ptconfig.put("type", type); }

void ConfigItem::setType(DataType type) {
  ptconfig.put("type", cd::dataTypeToString(type));
}

std::string ConfigItem::getName() {
  if (ptconfig.get_optional<std::string>("name")) {
    return ptconfig.get<std::string>("name");
  } else {
    throw std::runtime_error("does not contain name");
  }
}

void ConfigItem::setName(std::string name) { ptconfig.put("name", name); }

std::string ConfigItem::getDescription() {
  if (ptconfig.get_optional<std::string>("description")) {
    return ptconfig.get<std::string>("description");
  } else {
    return "";
  }
}

void ConfigItem::setDescription(std::string description) {
  ptconfig.put("description", description);
}

long ConfigItem::getMin() {
  if (ptconfig.get_optional<long>("min")) {
    return ptconfig.get<long>("min");
  } else {
    return 0;
  }
}

void ConfigItem::setMin(long min) { ptconfig.put("min", min); }

long ConfigItem::getMax() {
  if (ptconfig.get_optional<long>("max")) {
    return ptconfig.get<long>("max");
  } else {
    return 0;
  }
}

void ConfigItem::setMax(long max) { ptconfig.put("max", max); }

std::string ConfigItem::toString() {
  std::stringstream ss;
  boost::property_tree::write_json(ss, ptconfig);
  return ss.str();
}
}
