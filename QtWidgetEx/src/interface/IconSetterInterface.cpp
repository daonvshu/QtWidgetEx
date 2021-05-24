#include "interface/IconSetterInterface.h"

EX_BEGIN_NAMESPACE
IconSetterInterface::IconSetterInterface(IconSetterCallback* iconSetterCallback, QObject* parent)
    : ImageSetterInterface(nullptr, parent)
    , iconSetterCallback(iconSetterCallback)
{
    
}

IconSetterInterface::~IconSetterInterface() {
    
}

void IconSetterInterface::setDataInMainThread(const QVariant& value) {
    if (iconSetterCallback != nullptr) {
        QIcon target;
        auto size = targetSize;
        switch (value.type()) {
        case QVariant::Pixmap:
            {
                auto pixmap = value.value<QPixmap>();
                if (!pixmap.isNull()) {
                    if (size.width() == -1) {
                        size.setWidth(qRound(size.height() * pixmap.width() * 1.0 / pixmap.height()));
                    } else if (size.height() == -1) {
                        size.setHeight(qRound(size.width() * pixmap.height() * 1.0 / pixmap.width()));
                    }
                    target = QIcon(pixmap);
                }
            }
            break;
        case QVariant::Icon:
            target = value.value<QIcon>();
            break;
        }
        if (!target.isNull()) {
            iconSetterCallback->setIconSync(target, targetIsSet, size);
        }
    }
}

void IconSetterInterface::operator=(const QPixmap& pximap) {
    setValue(pximap);
}

void IconSetterInterface::operator=(const QImage& image) {
    setValue(QPixmap::fromImage(image));
}

void IconSetterInterface::operator=(const QString& imagePath) {
    setValue(QPixmap(imagePath));
}

void IconSetterInterface::operator=(const QIcon& icon) {
    setValue(icon);
}

void IconSetterInterface::operator=(const QBitmap& bitmap) {
}


EX_END_NAMESPACE