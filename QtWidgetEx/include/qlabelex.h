#pragma once

#include <qlabel.h>

#include "interface/textsetterinterface.h"
#include "interface/imagesetterinterface.h"
#include "interface/gifsetterinterface.h"

#include "eventex/mouseeventex.h"

class QLabelEx: public QLabel, _widget_ex::ImageSetterCallback, _widget_ex::GifSetterCallback
{
    Q_OBJECT

public:
    explicit QLabelEx(const QString& text, QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    explicit QLabelEx(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    _widget_ex::TextSetterInterface text;
    _widget_ex::ImageSetterInterface image;
    _widget_ex::GifSetterInterface gif;

    _widget_ex::MouseEventEx press;

protected:
    void setPixmapSync(const QPixmap& pixmap) override;
    void setImageSync(const QImage& image) override;
    //void setBitmapSync(const QBitmap& bitmap) override;

    void setMovie(QMovie* movie) override;
};