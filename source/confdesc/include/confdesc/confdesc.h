
#pragma once


#include <string>

#include <confdesc/confdesc_api.h>


namespace cd
{


/**
*  @brief
*    Print information about the library to the console
*/
CONFDESC_API void printInfo();

class CONFDESC_API  ConfDesc {

public:
    ConfDesc(std::string);

};


} // namespace cd
