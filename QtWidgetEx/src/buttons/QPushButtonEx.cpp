#include "QPushButtonEx.h"

EX_USING_NAMESPACE
QPushButtonEx::QPushButtonEx(const QString& text, QWidget* parent): QPushButtonEx(QIcon(), text, parent) {
}

QPushButtonEx::QPushButtonEx(const QIcon& icon, const QString& text, QWidget* parent)
    : QAbstractButtonEx<QPushButton>(parent)
{
    this->icon = icon;
    this->text = text;
}
