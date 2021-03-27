#pragma once

#include "AsyncDataSetter.h"

class TextSetterCallback {
public:
    virtual void setTextSync(const QString&) = 0;
};

class TextSetterInterface: AsyncDataSetter {
public:
    TextSetterInterface(TextSetterCallback* textSetterCallback, QObject* parent = nullptr);

    void operator=(const QVariant& data);

    QString operator()() const;

    typedef QString(*DataConvert)(const QVariant&);
    DataConvert dataConvert;

private:
    void setDataInMainThread(const QVariant& value) override;

private:
    TextSetterCallback* textSetterCallback;
};