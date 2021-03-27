#include "QLabelEx.h"

QLabelEx::QLabelEx(QWidget* parent, Qt::WindowFlags f): QLabelEx(QString(), parent, f) {}

QLabelEx::QLabelEx(const QString& text, QWidget* parent, Qt::WindowFlags f)
    : QLabel(text, parent, f)
    , text(this)
    , image(this)
{
}

void QLabelEx::setTextSync(const QString& string) {
    setText(string);
}

void QLabelEx::setPixmapSync(const QPixmap& pixmap) {
    setPixmap(pixmap);
}

void QLabelEx::setImageSync(const QImage& image) {
    setPixmap(QPixmap::fromImage(image));
}

void QLabelEx::setBitmapSync(const QBitmap& bitmap) {
    setMask(bitmap);
}
