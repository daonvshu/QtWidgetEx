#pragma once

#include <qobject.h>
#include <qvariant.h>
#include <qmutex.h>

#include "../exglobal.h"

EX_BEGIN_NAMESPACE
class AsyncDataSetter : public QObject {
    Q_OBJECT

public:
    explicit AsyncDataSetter(QObject* parent = nullptr);

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
EX_END_NAMESPACE