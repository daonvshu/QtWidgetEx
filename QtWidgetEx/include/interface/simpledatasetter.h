#pragma once

#include "asyncdatasetter.h"

#include <functional>
#include <qlocale.h>

EX_BEGIN_NAMESPACE
template<typename T>
class SimpleDataSetterCallback {
public:
    virtual void setData(const T&) = 0;
    virtual T getData() = 0;

    virtual ~SimpleDataSetterCallback() = default;
};

template<typename T, typename W>
class SimpleDataTargetSetterCallback : public SimpleDataSetterCallback<T>, QObject {
public:
    explicit SimpleDataTargetSetterCallback(W* widget) : QObject(widget), target(widget) {}

protected:
    W* target;
};

template<typename T>
class SimpleAsyncDataSetter : protected AsyncDataSetter {
public:
    explicit SimpleAsyncDataSetter(SimpleDataSetterCallback<T>* callback, QObject* parent = nullptr)
        : AsyncDataSetter(parent)
        , dataConvert(nullptr)
        , callback(callback)
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

    void replaceCallback(SimpleDataSetterCallback<T>* callback) {
        delete this->callback;
        this->callback = callback;
    }

    std::function<T(const QVariant&)> dataConvert;

    void applyPrecision(int prec, bool shortVer = false) {
        dataConvert = [=](const QVariant& data) {
            auto d = data.toDouble();
            if (shortVer) {
                return QString::number(QString::number(d, 'f', prec).toDouble(), 'f', QLocale::FloatingPointShortest);
            }
            return QString::number(d, 'f', prec);
        };
    }

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