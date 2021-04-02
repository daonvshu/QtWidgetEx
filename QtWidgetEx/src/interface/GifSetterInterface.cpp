#include "interface/GifSetterInterface.h"

EX_BEGIN_NAMESPACE
GifSetterInterface::GifSetterInterface(GifSetterCallback* callback, QObject* parent)
    : AsyncDataSetter(parent)
    , callback(callback)
    , gifRunner(nullptr)
{
}

void GifSetterInterface::operator=(const QString& gifPath) {
    setValue(gifPath);
}

void GifSetterInterface::setDataInMainThread(const QVariant& value) {
    if (callback != nullptr) {
        switch (value.type()) {
        case QVariant::String:
            {
                if (gifRunner == nullptr) {
                    gifRunner = new QMovie(this);
                    callback->setMovie(gifRunner);
                }
                gifRunner->setFileName(value.toString());
                gifRunner->start();
            }
            break;
        }
    }
}

EX_END_NAMESPACE