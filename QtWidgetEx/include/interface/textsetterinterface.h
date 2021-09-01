#pragma once

#include "simpledatasetter.h"

EX_BEGIN_NAMESPACE
class TextSetterInterface: public SimpleAsyncDataSetter<QString> {
public:
    explicit TextSetterInterface(SimpleDataSetterCallback<QString>* callback, QObject* parent = nullptr)
        : SimpleAsyncDataSetter<QString>(callback, parent) {}

    QVariant& last();

    void operator=(const QVariant& data);
};

template<typename T>
class TextSetterCallback : public SimpleDataTargetSetterCallback<QString, T> {
public:
    using SimpleDataTargetSetterCallback<QString, T>::SimpleDataTargetSetterCallback;

    void setData(const QString& text) override {
        SimpleDataTargetSetterCallback<QString, T>::target->setText(text);
    }

    QString getData() override {
        return SimpleDataTargetSetterCallback<QString, T>::target->text();
    }
};
EX_END_NAMESPACE
