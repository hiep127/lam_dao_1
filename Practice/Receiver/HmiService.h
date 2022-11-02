#ifndef HMISERVICE_H
#define HMISERVICE_H
#include <QThread>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <vector>
#include "../Service/ShareMem.h"

class AppMain;
class Model;
class HmiService : public QThread
{
    Q_OBJECT
public:
    HmiService(AppMain *app);
    ~HmiService();
    void run() override;

    std::vector<Data> getDataFromShareMem();

    void sendMQ(int index, Model mol);

signals:
    void datachanged(int index, Data data);

private:
    AppMain* m_appMain;
    bool isSender;
};

#endif // HMISERVICE_H
