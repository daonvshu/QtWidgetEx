#pragma once

#include <qlabel.h>

#include "interface/TextSetterInterface.h"
#include "interface/ImageSetterInterface.h"

class QLabelEx : public QLabel, TextSetterCallback, ImageSetterCallback {
public:
    explicit QLabelEx(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    explicit QLabelEx(const QString& text, QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    TextSetterInterface text;
    ImageSetterInterface image;

protected:
    void setTextSync(const QString&) override;

    void setPixmapSync(const QPixmap&) override;
    void setImageSync(const QImage&) override;
    void setBitmapSync(const QBitmap&) override;
};