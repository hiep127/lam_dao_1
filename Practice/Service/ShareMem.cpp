#include "ShareMem.h"

ShareMem::ShareMem()
{

}

void ShareMem::WriteData(std::string name, std::vector<Data> listData)
{
    std::string nameSize = name + "_size";
    int fdSize = shm_open(nameSize.c_str(), O_CREAT | O_RDWR, 0600); //| O_EXCL
    if (fdSize < 0) {
        std::cout << "fdSize open share mem fail";
        return;
    }

    size_t sizeOfList = listData.size();

    ftruncate(fdSize, sizeof(int));
    int *size = (int *)mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fdSize, 0);
    *size = sizeOfList;
    munmap(size, sizeof(int));
    close(fdSize);


    int fdData = shm_open(name.c_str(), O_CREAT | O_RDWR, 0600); //| O_EXCL
    if (fdData < 0) {
        std::cout << "fdData open share mem fail";
        return;
    }

    ftruncate(fdData, sizeOfList* sizeof(Data));
    Data *list = (Data *)mmap(0, sizeOfList* sizeof(Data), PROT_READ | PROT_WRITE, MAP_SHARED, fdData, 0);
    for(size_t i = 0; i < listData.size(); i++){
        strcpy(list[i].name, listData.at(i).name);
        list[i].assem = listData.at(i).assem;
        list[i].cpp = listData.at(i).cpp;
        list[i].js = listData.at(i).js;
        list[i].qml = listData.at(i).qml;
        list[i].openGL = listData.at(i).openGL;
    }

    munmap(size, sizeof(int));
    close(fdData);
}

std::vector<Data> ShareMem::ReadData(std::string name)
{
    std::cout << "ReadData" << std::endl;
    std::vector<Data> ret;
    std::string nameSize = name + "_size";
    int fdSize = shm_open(nameSize.c_str(), O_RDONLY, 0600);
    if (fdSize < 0) {
        std::cout << "open share mem fail";
        return ret;
    }

    int *size = (int *)mmap(0, sizeof(int), PROT_READ, MAP_SHARED, fdSize, 0);

    int fdData = shm_open(name.c_str(), O_RDONLY, 0600);
    if (fdData < 0) {
        std::cout << "open share mem fail";
        return ret;
    }
    Data *list = (Data *)mmap(0, *size* sizeof(Data), PROT_READ, MAP_SHARED, fdData, 0);
    for(int i = 0; i < *size; i++){
//        std::cout << list[i].name << std::endl;
//        std::cout << list[i].assem << std::endl;
//        std::cout << list[i].cpp << std::endl;
//        std::cout << list[i].js << std::endl;
//        std::cout << list[i].qml << std::endl;
//        std::cout << list[i].openGL << std::endl;

        Data tmp;
        strcpy(tmp.name, list[i].name);
        tmp.assem = list[i].assem;
        tmp.cpp = list[i].cpp;
        tmp.js = list[i].js;
        tmp.qml = list[i].qml;
        tmp.openGL = list[i].openGL;
        ret.push_back(tmp);
    }
    return ret;
}
