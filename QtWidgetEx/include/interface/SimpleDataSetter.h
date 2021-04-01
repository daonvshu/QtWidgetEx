#pragma once

#include "AsyncDataSetter.h"

EX_BEGIN_NAMESPACE
template<typename T>
class SimpleDataSetterCallback {
public:
    virtual void setData(const T&) = 0;
    virtual T getData() = 0;
};

template<typename T, typename W>
class SimpleDataTargetSetterCallback : public SimpleDataSetterCallback<T>, QObject {
public:
    explicit SimpleDataTargetSetterCallback(W* widget) : target(widget), QObject(widget) {}

protected:
    W* target;
};

template<typename T>
class SimpleAsyncDataSetter : protected AsyncDataSetter {
public:
    explicit SimpleAsyncDataSetter(SimpleDataSetterCallback<T>* callback, QObject* parent = nullptr)
        : AsyncDataSetter(parent)
        , callback(callback)
        , dataConvert(nullptr)
    {}

    T last() const {
        return lastSetData.value<T>();
    }

    void operator=(const T& data) {
        setValue(data);
    }

    T operator()() const {
        return callback->getData();
    }

    typedef T(*DataConvert)(const QVariant&);
    DataConvert dataConvert;

private:
    void setDataInMainThread(const QVariant& value) override {
        if (dataConvert == nullptr) {
            callback->setData(value.value<T>());
        } else {
            callback->setData(dataConvert(value));
        }
    }

private:
    SimpleDataSetterCallback<T>* callback;
};

EX_END_NAMESPACE