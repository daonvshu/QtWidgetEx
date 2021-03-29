#pragma once

#include <qlabel.h>

#include "interface/TextSetterInterface.h"
#include "interface/ImageSetterInterface.h"

#include "eventex/MouseEventEx.h"

class QLabelEx : public QLabel, TextSetterCallback, ImageSetterCallback {
    Q_OBJECT

public:
    explicit QLabelEx(const QString& text, QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    explicit QLabelEx(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    TextSetterInterface text;
    ImageSetterInterface image;

    MouseEventEx press;

protected:
    void setTextSync(const QString&) override;

    void setPixmapSync(const QPixmap&) override;
    void setImageSync(const QImage&) override;
    void setBitmapSync(const QBitmap&) override;
};