#ifndef CONFDESC_H
#define CONFDESC_H

#include <boost/property_tree/ptree.hpp>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#include <confdesc/confdesc_api.h>
#include <confdesc/configitem.h>

namespace cd {

/**
*  @brief
*    Print information about the library to the console
*/
CONFDESC_API void printInfo();

class CONFDESC_API ConfDesc {
 public:
  ConfDesc(std::string json);

  using iterator = std::map<std::string, cd::ConfigItem>::iterator;
  using const_iterator = std::map<std::string, cd::ConfigItem>::const_iterator;

  iterator begin() { return items.begin(); }

  iterator end() { return items.end(); }

  const_iterator cbegin() const { return items.cbegin(); }

  const_iterator cend() const { return items.cend(); }

 protected:
  boost::property_tree::ptree ptconfig;

  std::map<std::string, cd::ConfigItem> items;
};

}  // namespace cd

#endif
