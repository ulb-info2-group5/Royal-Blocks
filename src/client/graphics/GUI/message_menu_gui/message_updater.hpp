// message_updater.hpp
// Authors: Rafaou, Jonas, Ernest

#ifndef MESSAGE_UPDATER_HPP
#define MESSAGE_UPDATER_HPP

#include <QObject>
#include <QTimer>
#include "../../../core/controller/controller.hpp"

class MessageUpdater : public QObject {
    Q_OBJECT

public:
    explicit MessageUpdater(Controller &controller, QObject *parent = nullptr);
    ~MessageUpdater();

signals:
    void newMessagesFetched();

public slots:
    void checkForNewMessages();

private:
    Controller &controller_;
    QTimer *timer_;
};

#endif // MESSAGE_UPDATER_HPP
