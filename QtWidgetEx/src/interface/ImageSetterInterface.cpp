#include "interface/ImageSetterInterface.h"

#include "utils/NetworkImageGetter.h"

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
    setValue(scaledIfTargetSizeIsSet(pixmap));
}

void ImageSetterInterface::operator=(const QImage& image) {
    setValue(scaledIfTargetSizeIsSet(image));
}

void ImageSetterInterface::operator=(const QBitmap& bitmap) {
    setValue(scaledIfTargetSizeIsSet(bitmap));
}

void ImageSetterInterface::operator=(const QString& imagePath) {
    setValue(scaledIfTargetSizeIsSet(imagePath));
}

ImageSetterInterface& ImageSetterInterface::target(const QSize& size, Qt::AspectRatioMode aspectRatioMode, Qt::TransformationMode transformMode) {
    targetIsSet = true;
    targetSize = size;
    targetAspectRatio = aspectRatioMode;
    targetTransform = transformMode;
    return *this;
}

#ifdef CONFIG_NETWORK_IMG
ImageSetterInterface& ImageSetterInterface::network2(const QString& url, const QPixmap& placeholder, const QPixmap& err) {
    if (!lastLoadNetworkImg.isEmpty()) {
        if (lastLoadNetworkImg != url) {
            QPixmapCache::remove(lastLoadNetworkImg);
        }
    }
    lastLoadNetworkImg = url;

    QPixmap pixmapTag;
    if (!QPixmapCache::find(url, &pixmapTag)) {
        setValue(placeholder);

        auto getter = new NetworkImageGetter(url);
        connect(getter, &NetworkImageGetter::hasErr, this, [=](int) {
            setValue(err);
        });

        connect(getter, &NetworkImageGetter::getImage, this, [=](QPixmap pixmap) {
            auto target = scaledIfTargetSizeIsSet(pixmap);
            QPixmapCache::insert(url, target);
            setValue(target);
        });
        getter->start();
    } else {
        setValue(pixmapTag);
    }
    return *this;
}
#endif

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