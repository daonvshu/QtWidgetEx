#include "interface/textsetterinterface.h"

EX_BEGIN_NAMESPACE
QVariant& TextSetterInterface::last() {
    return lastSetData;
}

void TextSetterInterface::operator=(const QVariant& data) {
    setValue(data);
}
EX_END_NAMESPACE