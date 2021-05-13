#pragma once

#include "AsyncDataSetter.h"

#include <qpixmap.h>
#include <qimage.h>
#include <qbitmap.h>
#include <qpixmapcache.h>

#include "utils/NetworkImageGetter.h"

EX_BEGIN_NAMESPACE
class ImageSetterCallback {
public:
    virtual void setPixmapSync(const QPixmap&) = 0;
    virtual void setImageSync(const QImage&) = 0;
    virtual void setBitmapSync(const QBitmap&) = 0;
};

class ImageSetterInterface: AsyncDataSetter {
public:
    explicit ImageSetterInterface(ImageSetterCallback* imageSetterCallback, QObject* parent = nullptr);

    ~ImageSetterInterface();

private:
    void setDataInMainThread(const QVariant& value) override;

public:
    void operator=(const QPixmap& pixmap);
    void operator=(const QImage& image);
    void operator=(const QBitmap& bitmap);

    void operator=(const QString& imagePath);

    ImageSetterInterface& target(
        const QSize& size,
        Qt::AspectRatioMode aspectRatioMode = Qt::KeepAspectRatio, 
        Qt::TransformationMode transformMode = Qt::SmoothTransformation
    );

    ImageSetterInterface& target(
        int w, int h,
        Qt::AspectRatioMode aspectRatioMode = Qt::KeepAspectRatio,
        Qt::TransformationMode transformMode = Qt::SmoothTransformation
    ) {
        return target(QSize(w, h), aspectRatioMode, transformMode);
    }

    inline ImageSetterInterface& network(
        const QString& url,
        const QString& placeholder = QString(),
        const QString& err = QString()
    );

    inline ImageSetterInterface& network2(
        const QString& url,
        const QPixmap& placeholder = QPixmap(),
        const QPixmap& err = QPixmap()
    );

private:
    ImageSetterCallback* imageSetterCallback;

    bool targetIsSet;
    QSize targetSize;
    Qt::AspectRatioMode targetAspectRatio;
    Qt::TransformationMode targetTransform;

    bool networkCache;
    QString lastLoadNetworkImg;
};

//use inline to load network module optional

inline ImageSetterInterface& ImageSetterInterface::network(const QString& url, const QString& placeholder, const QString& err) {
    if (targetIsSet) {
        return network2(
            url,
            placeholder.isNull() ? placeholder : QPixmap(placeholder).scaled(targetSize, targetAspectRatio, targetTransform),
            err.isNull() ? err : QPixmap(err).scaled(targetSize, targetAspectRatio, targetTransform)
        );
    }
    return network2(url, QPixmap(placeholder), QPixmap(err));
}

inline ImageSetterInterface& ImageSetterInterface::network2(const QString& url, const QPixmap& placeholder, const QPixmap& err) {

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
            QPixmap target;
            if (targetIsSet) {
                target = QPixmap(pixmap).scaled(targetSize, targetAspectRatio, targetTransform);
            } else {
                target = pixmap;
            }
            QPixmapCache::insert(url, target);
            setValue(target);
        });
        getter->start();
    } else {
        setValue(pixmapTag);
    }
    return *this;
}
EX_END_NAMESPACE