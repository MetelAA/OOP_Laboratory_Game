//
// Created by Artem on 20.11.2025.
//

#ifndef LABAOOP2_READRIGHTJSON_H
#define LABAOOP2_READRIGHTJSON_H

#include <string>

class ReadRightJson {
public:
    static std::string read(const std::string& fileName);
    static void write(const std::string& json, const std::string& fileName);
};


#endif //LABAOOP2_READRIGHTJSON_H
