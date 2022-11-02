#ifndef DEFINE_H
#define DEFINE_H

struct Data{
    char  name[30];
    int assem;
    int cpp;
    int js;
    int qml;
    int openGL;
};

struct Message {
    long mesg_type;
    int index;
    Data data;
};

#endif // DEFINE_H
