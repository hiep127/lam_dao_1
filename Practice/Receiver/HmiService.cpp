#include "HmiService.h"
#include <QDebug>
#include "AppMain.h"

HmiService::HmiService(AppMain *app)
{
    m_appMain = app;
    isSender = false;
}

HmiService::~HmiService()
{

}

void HmiService::run()
{
    if(!isSender){
        key_t key = ftok("/media/sf_Project/Practice/mq/mqReceive", 68);
        int msgid = msgget(key, 0666 | IPC_CREAT);
        qDebug() << "Run";
        while(true) {
            // msgrcv to receive message
            Message mess;
            msgrcv(msgid, &mess, sizeof(mess), 1, 0);
            // display the message
            qDebug() << "Data Received is" << mess.data.assem;
            emit datachanged(mess.index, mess.data);
        }
//        // to destroy the message queue
//        msgctl(msgid, IPC_RMID, NULL);
    }
}

std::vector<Data> HmiService::getDataFromShareMem()
{
    ShareMem sm;
    return sm.ReadData("/ShareMem");
}

void HmiService::sendMQ(int index, Model mol)
{
    qDebug() << "Send MQ";
    key_t key = ftok("/media/sf_Project/Practice/mq/mqSender", 67);
    int msgid = msgget(key, 0666 | IPC_CREAT);

    qDebug() << "Prepare data for send";
    // msgrcv to receive message
    Message mess;
    mess.mesg_type = 1;
    mess.index = index;
    strcpy(mess.data.name, mol.getName().toLocal8Bit().data());
    mess.data.assem = mol.getAssembly();
    mess.data.cpp = mol.getCpp();
    mess.data.js = mol.getJavaScript();
    mess.data.qml = mol.getQML();
    mess.data.openGL = mol.getOpenGL();

    msgsnd(msgid, &mess, sizeof(mess), 0);
    qDebug() << "Data is sent";
}
