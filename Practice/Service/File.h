#ifndef FILE_H
#define FILE_H

#include "Define.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "include/nlohmann/json.hpp"
using json = nlohmann::json;


class File
{
public:
    File();
    std::vector<Data> getDataFromFile(const std::string& fileName);

};

#endif // FILE_H
