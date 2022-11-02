#include "Service.h"
#include "File.h"
#include <unistd.h>

Service::Service()
{
    File file;
    m_data = file.getDataFromFile("test.json");
    ShareMem sm;
    sm.WriteData("/ShareMem", m_data);
    std::cout << "Done share mem" << std::endl;
}
