#ifndef CONFIGITEM_H
#define CONFIGITEM_H

#include <confdesc/confdesc_api.h>
#include <confdesc/datatypes.h>
#include <boost/property_tree/ptree.hpp>
#include <stdexcept>
#include <string>

namespace cd {

class CONFDESC_API ConfigItem {
 public:
  ConfigItem();
  ConfigItem(std::string json);
  ConfigItem(boost::property_tree::ptree ptconfig);

  DataType getType();
  std::string getTypeAsString();
  void setType(std::string type);
  void setType(cd::DataType type);

  std::string getName();
  void setName(std::string name);

  std::string getDescription();
  void setDescription(std::string description);

  long getMin();
  void setMin(long min);

  long getMax();
  void setMax(long max);

  template <typename Type>
  Type getValue() {
    if (ptconfig.get_optional<Type>("value")) {
      return ptconfig.get<Type>("value");
    } else {
      throw std::runtime_error("does not contain value");
    }
  }

  template <typename Type>
  void setValue(Type value) {
    ptconfig.put("value", value);
  }

  std::string toString();

 protected:
  boost::property_tree::ptree ptconfig;
};
}

#endif  // CONFIGITEM_H
