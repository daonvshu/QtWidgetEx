#pragma once

#include <interface/AsyncDataSetter.h>

using namespace _widget_ex;
class AsyncSetterTest : public AsyncDataSetter {
public:
    using AsyncDataSetter::AsyncDataSetter;

    void start();

protected:
    void setDataInMainThread(const QVariant& value) override;
};