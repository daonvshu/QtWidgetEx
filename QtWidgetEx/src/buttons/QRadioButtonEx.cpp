#include "QRadioButtonEx.h"

QRadioButtonEx::QRadioButtonEx(const QString& text, QWidget* parent)
    : QAbstractButtonEx<QRadioButton>(parent)
{
    this->text = text;
}
