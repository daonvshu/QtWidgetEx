#pragma once

#include <interface/AsyncDataSetter.h>

using namespace _widget_ex;
class AsyncSetterTest : public AsyncDataSetter {
    Q_OBJECT

public:
    using AsyncDataSetter::AsyncDataSetter;

    void start();

signals:
    void postValue3(const QVariant&);

protected:
    void setDataInMainThread(const QVariant& value) override;

    void setValue2(const QVariant&);

    void setValue3(const QVariant&);
};