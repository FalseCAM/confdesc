#ifndef DATATYPES_H
#define DATATYPES_H

#include <string>

namespace cd{

enum class DataType { BOOLEAN, INTEGER, FLOAT,
                                    STRING, UNKNOWN};

static std::string dataTypeToString(DataType datatype){
    if(datatype == DataType::BOOLEAN)
        return "boolean";
    if(datatype == DataType::INTEGER)
        return "integer";
    if(datatype == DataType::FLOAT)
        return "float";
    if(datatype == DataType::STRING)
        return "string";
    else
        return "unknown";
}

static DataType dataTypeFromString(std::string datatype){
    if(datatype == "boolean")
        return DataType::BOOLEAN;
    if(datatype == "integer")
        return DataType::INTEGER;
    if(datatype == "float")
        return DataType::FLOAT;
    if(datatype == "string")
        return DataType::STRING;
    return DataType::UNKNOWN;
}

}

#endif // DATATYPES_H

