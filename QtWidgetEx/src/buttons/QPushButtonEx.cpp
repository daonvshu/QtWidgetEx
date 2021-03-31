#include "QPushButtonEx.h"

QPushButtonEx::QPushButtonEx(QWidget* parent): QPushButtonEx(QString(), parent) {
}

QPushButtonEx::QPushButtonEx(const QString& text, QWidget* parent): QPushButtonEx(QIcon(), text, parent) {
}

QPushButtonEx::QPushButtonEx(const QIcon& icon, const QString& text, QWidget* parent)
    : QPushButton(icon, text, parent)
    , clickEvt(this, &QPushButtonEx::clicked)
    , pressEvt(this, &QPushButtonEx::pressed)
    , releaseEvt(this, &QPushButtonEx::released)
    , toggleEvt(this, &QPushButtonEx::toggled)
    , text(this, this)
{

}

void QPushButtonEx::setTextSync(const QString& string) {
    setText(string);
}
