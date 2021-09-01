#pragma once

#include "asyncdatasetter.h"

#include <qmovie.h>

EX_BEGIN_NAMESPACE
class GifSetterCallback {
public:
    virtual void setMovie(QMovie* movie) = 0;
};

class GifSetterInterface: AsyncDataSetter {
public:
    explicit GifSetterInterface(GifSetterCallback* callback, QObject* parent = nullptr);

private:
    void setDataInMainThread(const QVariant& value) override;

public:
    void operator=(const QString& gifPath);

    QMovie* operator()() {
        return gifRunner;
    }

private:
    GifSetterCallback* callback;
    QMovie* gifRunner;
};
EX_END_NAMESPACE