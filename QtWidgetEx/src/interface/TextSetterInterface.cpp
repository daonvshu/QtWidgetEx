#include "interface/TextSetterInterface.h"

TextSetterInterface::TextSetterInterface(TextSetterCallback* textSetterCallback, QObject* parent)
    : AsyncDataSetter(parent)
    , textSetterCallback(textSetterCallback)
    , dataConvert(nullptr)
{
}

void TextSetterInterface::operator=(const QVariant& data) {
    setValue(data);
}

QString TextSetterInterface::operator()() const {
    return lastSetData.toString();
}

void TextSetterInterface::setDataInMainThread(const QVariant& value) {
    if (textSetterCallback != nullptr) {
        if (dataConvert == nullptr) {
            textSetterCallback->setTextSync(value.toString());
        } else {
            textSetterCallback->setTextSync(dataConvert(value));
        }
    }
}

