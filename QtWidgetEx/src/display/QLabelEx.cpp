#include "QLabelEx.h"

EX_USING_NAMESPACE
QLabelEx::QLabelEx(QWidget* parent, Qt::WindowFlags f): QLabelEx(QString(), parent, f) {}

QLabelEx::QLabelEx(const QString& text, QWidget* parent, Qt::WindowFlags f)
    : QLabel(text, parent, f)
    , text(new TextSetterCallback<QLabel>(this))
    , image(this)
    , press(this)
    , gif(this)
{
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

void QLabelEx::setMovie(QMovie* movie) {
    QLabel::setMovie(movie);
}
