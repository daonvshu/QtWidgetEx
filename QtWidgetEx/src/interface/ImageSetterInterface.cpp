#include "interface/ImageSetterInterface.h"

EX_BEGIN_NAMESPACE
ImageSetterInterface::ImageSetterInterface(ImageSetterCallback* imageSetterCallback, QObject* parent)
    : AsyncDataSetter(parent)
    , imageSetterCallback(imageSetterCallback)
    , targetIsSet(false)
    , networkCache(true)
{
}

ImageSetterInterface::~ImageSetterInterface() {
    if (!lastLoadNetworkImg.isEmpty()) {
        QPixmapCache::remove(lastLoadNetworkImg);
    }
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

void ImageSetterInterface::operator=(const QString& imagePath) {
    setValue(QPixmap(imagePath));
}

ImageSetterInterface& ImageSetterInterface::target(const QSize& size, Qt::AspectRatioMode aspectRatioMode, Qt::TransformationMode transformMode) {
    targetIsSet = true;
    targetSize = size;
    targetAspectRatio = aspectRatioMode;
    targetTransform = transformMode;
    return *this;
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