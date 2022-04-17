#pragma once

#include "asyncdatasetter.h"

#include <qpixmap.h>
#include <qimage.h>
#include <qbitmap.h>
#include <qpixmapcache.h>

EX_BEGIN_NAMESPACE
class ImageSetterCallback {
public:
    virtual void setPixmapSync(const QPixmap&) = 0;
    virtual void setImageSync(const QImage&) = 0;
    virtual void setBitmapSync(const QBitmap&) = 0;
};

class ImageSetterInterface: protected AsyncDataSetter {
public:
    explicit ImageSetterInterface(ImageSetterCallback* imageSetterCallback, QObject* parent = nullptr);

    ~ImageSetterInterface();

private:
    void setDataInMainThread(const QVariant& value) override;

public:
    virtual void operator=(const QPixmap& pixmap);
    virtual void operator=(const QImage& image);
    virtual void operator=(const QBitmap& bitmap);

    virtual void operator=(const QString& imagePath);

    ImageSetterInterface& target(
        const QSize& size,
        Qt::AspectRatioMode aspectRatioMode = Qt::KeepAspectRatio, 
        Qt::TransformationMode transformMode = Qt::SmoothTransformation
    );

    inline ImageSetterInterface& target(
        int w, int h,
        Qt::AspectRatioMode aspectRatioMode = Qt::KeepAspectRatio,
        Qt::TransformationMode transformMode = Qt::SmoothTransformation
    ) {
        return target(QSize(w, h), aspectRatioMode, transformMode);
    }

    inline ImageSetterInterface& targetW(
        int w,
        Qt::AspectRatioMode aspectRatioMode = Qt::KeepAspectRatio,
        Qt::TransformationMode transformMode = Qt::SmoothTransformation
    ) {
        return target(w, -1, aspectRatioMode, transformMode);
    }

    inline ImageSetterInterface& targetH(
        int h,
        Qt::AspectRatioMode aspectRatioMode = Qt::KeepAspectRatio,
        Qt::TransformationMode transformMode = Qt::SmoothTransformation
    ) {
        return target(-1, h, aspectRatioMode, transformMode);
    }

    inline ImageSetterInterface& noScale() {
        targetIsSet = false;
        return *this;
    }

#ifdef CONFIG_NETWORK_IMG
    inline ImageSetterInterface& network(
        const QString& url,
        const QString& placeholder = QString(),
        const QString& err = QString()
    ) {
        return network2(url, scaledIfTargetSizeIsSet(placeholder), scaledIfTargetSizeIsSet(err));
    }

    ImageSetterInterface& network2(
        const QString& url,
        const QPixmap& placeholder = QPixmap(),
        const QPixmap& err = QPixmap()
    );
#endif

protected:
    ImageSetterCallback* imageSetterCallback;

    bool targetIsSet;
    QSize targetSize;
    Qt::AspectRatioMode targetAspectRatio;
    Qt::TransformationMode targetTransform;

    bool networkCache;
    QString lastLoadNetworkImg;

protected:
    template<typename T>
    inline T scaledIfTargetSizeIsSet(const T& source) {
        if (!source.isNull() && targetIsSet) {
            if (targetSize.width() == -1) {
                return source.scaledToHeight(targetSize.height(), targetTransform);
            } else if (targetSize.height() == -1) {
                return source.scaledToWidth(targetSize.width(), targetTransform);
            }
            return source.scaled(targetSize, targetAspectRatio, targetTransform);
        }
        return source;
    }

    inline QPixmap scaledIfTargetSizeIsSet(const QString& source) {
        return scaledIfTargetSizeIsSet(QPixmap(source));
    }

#ifdef CONFIG_NETWORK_IMG
    void requestImageFromNetwork(const QString& url, const QPixmap& err, int requestCount);
#endif
};

EX_END_NAMESPACE