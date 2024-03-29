﻿#include "interface/asyncdatasetter.h"

#include <qthread.h>

EX_BEGIN_NAMESPACE
AsyncDataSetter::AsyncDataSetter(QObject* parent)
    : QObject(parent)
{
    mainThread = QThread::currentThreadId();

    connect(this, &AsyncDataSetter::setDataAsync, 
        this, &AsyncDataSetter::pendingToSetValue, Qt::QueuedConnection);
}

void AsyncDataSetter::pendingToSetValue() {
    mutex.lock();
    lastSetData = pendingData;
    pendingData = QVariant();
    mutex.unlock();
    setDataInMainThread(lastSetData);
}

void AsyncDataSetter::setValue(const QVariant& value) {
    if (QThread::currentThreadId() == mainThread) {
        lastSetData = value;
        setDataInMainThread(lastSetData);
    } else {
        bool needRequestTask = false;
        mutex.lock();
        needRequestTask = pendingData.isNull();
        pendingData = value;
        mutex.unlock();
        if (needRequestTask) {
            emit setDataAsync(QPrivateSignal());
        }
    }
}
EX_END_NAMESPACE