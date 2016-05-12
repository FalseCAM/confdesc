#ifndef CONFIGITEM_H
#define CONFIGITEM_H

#include <confdesc/datatypes.h>
#include <string>
#include <stdexcept>

namespace cd {

class ConfigItem {
public:
  ConfigItem(std::string json);


  std::string getType();
  std::string getName();
  long getMin();
  long getMax();

  template<class T> T getValue(){ return std::invalid_argument("Type not supported!"); }

protected:

  void parse();
  void parseValue();

  std::string json;

  std::string name;

  cd::DataType type;

  long intValue;
  std::string strValue;
  double floatValue;
  bool boolValue;

  long min;
  long max;
};
}

#endif // CONFIGITEM_H
