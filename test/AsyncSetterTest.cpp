#include "AsyncSetterTest.h"

#include "utils/RunnableHandler.h"

#include <qdatetime.h>
#include <qdebug.h>

void AsyncSetterTest::start() {
    RunnableHandler<void>::exec([&] {
        qint64 st = QDateTime::currentMSecsSinceEpoch();
        for (int i = 0; i < 100000; i++) {
            QString data = "index: " + QString::number(i);
            //qDebug() << "send value: " << data;
            setValue2(data);
        }
        qDebug() << "test setter run time:" << (QDateTime::currentMSecsSinceEpoch() - st);
    });

    RunnableHandler<void>::exec([&] {
        qint64 st = QDateTime::currentMSecsSinceEpoch();
        for (int i=0; i<100000; i++) {
            QString data = "index: " + QString::number(i);
            //qDebug() << "send value 2: " << data;
            setValue(data);
        }
        qDebug() << "test setter run time 2:" << (QDateTime::currentMSecsSinceEpoch() - st);
    });

    RunnableHandler<void>::exec([&] {
        connect(this, &AsyncSetterTest::postValue3, this, &AsyncSetterTest::setValue3);
        qint64 st = QDateTime::currentMSecsSinceEpoch();
        for (int i = 0; i < 100000; i++) {
            QString data = "index: " + QString::number(i);
            //qDebug() << "send value 2: " << data;
            postValue3(data);
        }
        qDebug() << "test setter run time 3:" << (QDateTime::currentMSecsSinceEpoch() - st);
        disconnect(this, &AsyncSetterTest::postValue3, this, &AsyncSetterTest::setValue3);
    });
}

void AsyncSetterTest::setDataInMainThread(const QVariant& value) {
    qDebug() << "receive value 2: " << value;
}

void AsyncSetterTest::setValue2(const QVariant& value) {
    qDebug() << "receive value: " << value;
}

void AsyncSetterTest::setValue3(const QVariant& value) {
    qDebug() << "receive value 3: " << value;
}

