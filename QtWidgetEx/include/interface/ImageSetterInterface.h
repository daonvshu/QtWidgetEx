#pragma once

#include "AsyncDataSetter.h"

#include <qpixmap.h>
#include <qimage.h>
#include <qbitmap.h>

class ImageSetterCallback {
public:
    virtual void setPixmapSync(const QPixmap&) = 0;
    virtual void setImageSync(const QImage&) = 0;
    virtual void setBitmapSync(const QBitmap&) = 0;
};

class ImageSetterInterface: AsyncDataSetter {
public:
    ImageSetterInterface(ImageSetterCallback* imageSetterCallback, QObject* parent = nullptr);

private:
    void setDataInMainThread(const QVariant& value) override;

    void operator=(const QPixmap& pixmap);
    void operator=(const QImage& image);
    void operator=(const QBitmap& bitmap);
    void operator=(const QByteArray& imageData);
    void operator=(const QString& base64Str);

private:
    ImageSetterCallback* imageSetterCallback;
};