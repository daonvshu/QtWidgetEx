﻿#include "interface/ImageSetterInterface.h"

EX_BEGIN_NAMESPACE
ImageSetterInterface::ImageSetterInterface(ImageSetterCallback* imageSetterCallback, QObject* parent)
    : AsyncDataSetter(parent)
    , imageSetterCallback(imageSetterCallback)
{
}

void ImageSetterInterface::operator=(const QPixmap& pixmap) {
    setValue(pixmap);
}

void ImageSetterInterface::operator=(const QImage& image) {
    setValue(image);
}

void ImageSetterInterface::operator=(const QBitmap& bitmap) {
    setValue(bitmap);
}

void ImageSetterInterface::operator=(const QString& base64Str) {
    setValue(QImage::fromData(QByteArray::fromBase64(base64Str.toLatin1())));
}

void ImageSetterInterface::setDataInMainThread(const QVariant& value) {
    if (imageSetterCallback != nullptr) {
        switch (value.type()) {
        case QVariant::Pixmap:
            imageSetterCallback->setPixmapSync(value.value<QPixmap>());
            break;
        case QVariant::Image:
            imageSetterCallback->setImageSync(value.value<QImage>());
            break;
        case QVariant::Bitmap:
            imageSetterCallback->setBitmapSync(value.value<QBitmap>());
            break;
        }
    }
}
EX_END_NAMESPACE