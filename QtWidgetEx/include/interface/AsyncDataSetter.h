#pragma once

#include <qobject.h>
#include <qvariant.h>
#include <qmutex.h>

class AsyncDataSetter : public QObject {
    Q_OBJECT

public:
    AsyncDataSetter(QObject* parent = nullptr);

signals:
    void setDataAsync(QPrivateSignal);

private:
    QMutex mutex;
    Qt::HANDLE mainThread;

    void pendingToSetValue();

protected:
    QVariant pendingData;
    QVariant lastSetData;

    void setValue(const QVariant& value);

    virtual void setDataInMainThread(const QVariant& value) = 0;
};