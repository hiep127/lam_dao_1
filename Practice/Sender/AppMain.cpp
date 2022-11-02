#include "AppMain.h"
#include <QDebug>

AppMain::AppMain(QObject *parent) : QObject(parent)
{
    m_service = new HmiService(this);
    qRegisterMetaType<Data>("Data");


    connect(m_service, SIGNAL(finished()),m_service, SLOT(deleteLater()));
    connect(m_service, SIGNAL(datachanged(int, Data)), this, SLOT(onDataChanged(int, Data)));
    m_service->start();

    initModel(m_service->getDataFromShareMem());
}

void AppMain::initContext(QQmlContext *context)
{
    if(context != nullptr){
        m_filterProxy.setSourceModel(&m_model);
        m_filterProxy.setFilterRole(ListModel::nameRole);
        m_filterProxy.setFilterCaseSensitivity(Qt::CaseInsensitive);
        context->setContextProperty("listModel",&m_filterProxy);
        context->setContextProperty("appMain",this);
    }
}

void AppMain::initModel(std::vector<Data> data)
{
    QList<Model>* list = m_model.getListModel();

    for(size_t i = 0; i < data.size(); ++i){
        Data tmp= data.at(i);
        list->append (Model(tmp.name, tmp.assem, tmp.cpp, tmp.js, tmp.qml, tmp.openGL));
    }
}

void AppMain::requestResfesh()
{
    qDebug() << __FUNCTION__ << __LINE__;
}

void AppMain::requestUpdateData(int index)
{
    qDebug() << __FUNCTION__ << " " << __LINE__ << " index = " << index;
    m_service->sendMQ(index, m_model.getListModel()->at(index));
}

void AppMain::onDataChanged(int index, Data data)
{
    Model tmp(data.name, data.assem, data.cpp, data.js, data.qml, data.openGL );

    m_model.getListModel()->replace(index, tmp);
    m_model.updateData(index);
    emit updateData();
}
