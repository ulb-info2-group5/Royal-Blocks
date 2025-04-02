// message_updater.cpp
// Authors: Rafaou, Jonas, Ernest

#include "message_updater.hpp"

MessageUpdater::MessageUpdater(Controller &controller, QObject *parent)
    : QObject(parent), controller_(controller) {
    
    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, this, &MessageUpdater::checkForNewMessages);
    timer_->start(1000); // Poll every 1 second
}

MessageUpdater::~MessageUpdater() {
    timer_->stop();
}

void MessageUpdater::checkForNewMessages() {
    emit newMessagesFetched();
}
