#include "File.h"

File::File()
{

}

std::vector<Data> File::getDataFromFile(const std::string &fileName)
{
    std::ifstream f("../Service/test.json");
    json data = json::parse(f);

    // create copies using iterators
    int dataRange = data.end() - data.begin();

    //serialize the values
    std::vector<Data> ret;
    for(int i=0; i<dataRange;i++)
    {
        Data temp;
        strcpy(temp.name, data[i].value("name", "oops").c_str());
        temp.assem =  stoi(data[i].value("ASS", "oops"));
        temp.cpp =  stoi(data[i].value("CPP", "oops"));
        temp.js =  stoi(data[i].value("JAV", "oops"));
        temp.qml =  stoi(data[i].value("QML", "oops"));
        temp.openGL =  stoi(data[i].value("OPE", "oops"));

        ret.push_back(temp);
    }

    return ret;
}
