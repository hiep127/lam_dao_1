#include "Service.h"
using namespace std;
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <iostream>
#include <stdio.h>
#include "Define.h"


void sendDataToReceiver(Message mess)
{
    std::cout <<"sendDataToReceiver " << std::endl;
    key_t key = ftok("/media/sf_Project/Practice/mq/mqReceive", 68);
    int id = msgget(key, 0666 | IPC_CREAT);
    msgsnd(id, &mess, sizeof(Message), 0);
}

void *receiveDataFromSender(void *arg)
{
    std::cout <<"receiveDataFromSender " << std::endl;
    key_t key = ftok("/media/sf_Project/Practice/mq/mqSender", 67);
    int id = msgget(key, 0666 | IPC_CREAT);
    Message mess;
    while(true) {
        std::cout <<  "Waiting Message " << std::endl;
        int result = msgrcv(id, (void *)&mess, sizeof(Message), 1, MSG_NOERROR);
        std::cout << "Result = " << result << std::endl;
        if (-1 == result)
            perror("error: ");

        std::cout <<"result " <<  result << std::endl;
        std::cout <<"Message type " <<  mess.mesg_type << std::endl;
        auto data = mess.data;
        std::cout << "Index = " << mess.index << std::endl;
        std::cout <<"Name = " << data.name << ", ass = " << data.assem << ", cpp = " << data.cpp << ", js = " << data.js << ", qml = "  << data.qml << ", openGL = " << data.openGL<< std::endl;

        // Send to receiver
        sendDataToReceiver(mess);
    }
}


int main()
{
    Service m_ser;

    pthread_t tid;
    pthread_create(&tid, NULL, receiveDataFromSender, NULL);

    pthread_join(tid, NULL);
    pthread_exit((void *)NULL);

    return 0;
}
