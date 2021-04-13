#include "AsyncSetterTest.h"

#include "utils/RunnableHandler.h"

#include <qdebug.h>

void AsyncSetterTest::start() {
    RunnableHandler<void>::exec([&] {
        for (int i=0; i<10000; i++) {
            QString data = "index: " + QString::number(i);
            qDebug() << "send value: " << data;
            setValue(data);
        }
    });
}

void AsyncSetterTest::setDataInMainThread(const QVariant& value) {
    qDebug() << "receive value: " << value;
}

