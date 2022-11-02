#ifndef SERVICE_H
#define SERVICE_H

#include <vector>
#include "ShareMem.h"

class Service
{
public:
    Service();
private:
    std::vector<Data> m_data;
};

#endif // SERVICE_H
