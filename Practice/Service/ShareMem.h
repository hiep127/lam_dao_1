#ifndef SHAREMEM_H
#define SHAREMEM_H

#include <string>
#include <string.h>
#include <vector>
#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include "Define.h"

class ShareMem
{
public:
    ShareMem();
    void WriteData(std::string name, std::vector<Data> listData);
    std::vector<Data> ReadData(std::string name);
};

#endif // SHAREMEM_H
