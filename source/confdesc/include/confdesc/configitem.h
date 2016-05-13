#ifndef CONFIGITEM_H
#define CONFIGITEM_H

#include <string>
#include <stdexcept>
#include <boost/property_tree/ptree.hpp>
#include <confdesc/datatypes.h>
#include <confdesc/confdesc_api.h>

namespace cd {

class CONFDESC_API ConfigItem {
public:
  ConfigItem(std::string json);

  DataType getType();
  std::string getTypeAsString();
  void setType(std::string type);
  void setType(cd::DataType type);

  std::string getName();
  void setName(std::string name);

  long getMin();
  void setMin(long min);

  long getMax();
  void setMax(long max);

  template<typename Type>
  Type getValue()
  {
      if (ptconfig.get_optional<Type>("value")) {
              return ptconfig.get<Type>("value");
            }else {
              throw std::runtime_error("does not contain value");
      }
  }

  template<typename Type>
  void setValue(Type value)
  {
      ptconfig.put("value", value);
  }

  std::string toString();

protected:

  boost::property_tree::ptree ptconfig;

  std::string json;
};
}

#endif // CONFIGITEM_H
