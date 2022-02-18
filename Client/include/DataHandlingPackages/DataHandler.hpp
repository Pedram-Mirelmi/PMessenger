#pragma once
#include <memory>
#include <string>
#include <QObject>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "../../Commons/KeyWords.hpp"
#include "DataBase.hpp"
#include "../NetworkPackages/NetworkHandler.hpp"
#include "./models/ConversationsListModel.hpp"
#include "./models/MessageListModel.hpp"

class MainApp;

class DataHandler : public QObject
{
    Q_OBJECT
    friend class MainApp;
    InfoContainer& m_user_info;

    DataBase* m_db;
    NetworkHandler* m_net_handler;
    MessageListModel* m_message_list_model;
    ConversationsListModel* m_conversation_list_model;

public:
    explicit DataHandler(QObject* parent, NetworkHandler* netHandler,
                         InfoContainer& user_info);

    Q_INVOKABLE void openPrivateChatWith(const quint64 user_id,
                                         const QString& name);

    Q_INVOKABLE void sendNewTextMessage(const quint64& env_id,
                                        const QString& message_text);

    Q_INVOKABLE void saveUser(const quint64& user_id,
                              const QString& username,
                              const QString& name);
public slots:
    void handleNewData(const QJsonObject& net_message);

    void fillConversationListModel();

    void registerAllPendingChats();

    void registerAllMessages();

public:
    void handleFetchResult(const QJsonObject& net_message);

    void fetchPrivateEnvDetails(const quint64& env_id);


    void prepareDB();
private:

    void openPendingPrivateChat(const InfoContainer& chat_info,
                                const QString& name,
                                const bool& newly_created);

    void openExistingPrivateChat(const InfoContainer& chat_info,
                                 const QString& name);

    void sendTextMessageToEnv(const quint16& env_id,
                              const QString& message_text,
                              const bool& to_pending);

// function for pending fils
    void feedEnvMessagesToMessagesModel(const quint64& env_id,
                                        const bool& is_pending_env);

    bool tryToCreatePendingFiles();

    void readPendingsFromFile();

    quint16 addNewPrivateChatToPendingChats(const quint64& user_id);

    void validatePrivateChat(const NetInfoContainer& env_info);

private:
    void convertToHash(InfoContainer& target, const QJsonObject& source);
};


