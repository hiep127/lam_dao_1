#ifndef APPMAIN_H
#define APPMAIN_H
#include "Model/ListModel.h"
#include <QQmlContext>
#include <QSortFilterProxyModel>
#include <QObject>
#include "HmiService.h"
#include "../Service/ShareMem.h"

class AppMain : public QObject
{
    Q_OBJECT
public:
    AppMain(QObject *parent = nullptr);

    void initContext(QQmlContext *context);
    void initModel(std::vector<Data> data);

    Q_INVOKABLE void requestResfesh();
    Q_INVOKABLE void requestUpdateData(int index);

private slots:
    void onDataChanged(int index, Data data);

signals:
    void updateData();

private:
    ListModel m_model;
    QSortFilterProxyModel m_filterProxy;
    HmiService* m_service;
};

#endif // APPMAIN_H
