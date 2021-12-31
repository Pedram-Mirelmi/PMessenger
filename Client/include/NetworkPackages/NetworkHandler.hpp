#pragma once
#include <QTcpSocket>
#include <QHostAddress>
#include <QJsonObject>
#include <QJsonDocument>
#include <string>
#include <cmath>
#include <QObject>
#include "../NetworkPackages/NetReceiver.hpp"
#include "../NetworkPackages/NetSender.hpp"

class MainApp;

class NetworkHandler : public QObject
{
    Q_OBJECT
    friend class MainApp;
    QTcpSocket* m_socket;
    const QHostAddress m_address;
    quint16 m_port;
    NetMessageReceiver* m_receiver;
public:
    NetMessageSender* m_sender;
    Q_PROPERTY(bool net_connected READ netConnected NOTIFY netConnectedChanged);
signals:
    void netConnectedChanged(bool connection_status);
public:
    explicit NetworkHandler(QObject* parent, const QString& address = "127.0.0.1", quint16 port = 54000);

    void setAutoConnect(bool enable);

    bool netConnected ();

    Q_INVOKABLE void sendRegisterReq(const QString& username, const QString& password);
    Q_INVOKABLE void sendLoginReq(const QString& username, const QString& password);
    Q_INVOKABLE void sendFetchReq();


public slots:
    void connectToServer();
    void handleNewNetMessage(const QJsonObject& net_msg);
private:
    bool net_connected = false;
signals:
    void newDataArrived(const QJsonObject& msg);
    void entryNetMessageArrived(const QJsonObject& msg);
    void userSearchResultArrived(const QJsonObject& msg);
    void newChatCreationMsgArrived(const QJsonObject& msg);
    void testSignal(QString s);
};
