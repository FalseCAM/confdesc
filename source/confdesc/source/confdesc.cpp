
#include <fstream>
#include <iostream>

#include <boost/foreach.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <confdesc/confdesc-version.h>

#include <confdesc/confdesc.h>
#include <confdesc/configitem.h>

namespace cd {

void printInfo() {
  std::string dataPath = "data";

  // Library name
  std::cout << "Library confdesc" << std::endl;
  std::cout << "========================================" << std::endl;

  // Library version
  std::cout << "Version: " << CONFDESC_VERSION << std::endl;
  std::cout << std::endl;

// Library type (static or dynamic)
#ifdef CONFDESC_STATIC_DEFINE
  std::cout << "Library type: STATIC" << std::endl;
#else
  std::cout << "Library type: SHARED" << std::endl;
#endif

  // Data directory
  std::cout << "Data path:    " << dataPath << std::endl;
  std::cout << std::endl;

  // Read file
  std::cout << "Data directory access" << std::endl;
  std::cout << "========================================" << std::endl;

  std::string fileName = dataPath + "/DATA_FOLDER.txt";
  std::cout << "Reading from '" << fileName << "': " << std::endl;
  std::cout << std::endl;

  std::ifstream f(fileName);
  if (f.is_open()) {
    std::string line;
    while (getline(f, line)) {
      std::cout << line << '\n';
    }
    f.close();
  } else {
    std::cout << "Unable to open file." << std::endl;
  }
}

ConfDesc::ConfDesc(std::string json) {
  std::stringstream ssconfig(json);
  boost::property_tree::read_json(ssconfig, ptconfig);
  if (ptconfig.get_child_optional("confdesc")) {
    BOOST_FOREACH (const boost::property_tree::ptree::value_type& child,
                   ptconfig.get_child("confdesc")) {
      boost::property_tree::ptree ptconfig = child.second;
      cd::ConfigItem item(ptconfig);
      items[item.getName()] = item;
    }
  }
}
}  // namespace cd
