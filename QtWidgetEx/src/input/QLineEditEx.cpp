#include "QLineEditEx.h"

#include <qvalidator.h>

EX_BEGIN_NAMESPACE
class ReadOnlySetterCallback : public SimpleDataTargetSetterCallback<bool, QLineEdit> {
public:
    using SimpleDataTargetSetterCallback::SimpleDataTargetSetterCallback;

    void setData(const bool& readOnly) override {
        target->setReadOnly(readOnly);
    }

    bool getData() override {
        return target->isReadOnly();
    }
};
EX_END_NAMESPACE

EX_USING_NAMESPACE
QLineEditEx::QLineEditEx(QWidget* parent): QLineEditEx(QString(), parent) {}

QLineEditEx::QLineEditEx(const QString& string, QWidget* parent)
    : QLineEdit(string, parent)
    , text(new TextSetterCallback<QLineEdit>(this))
    , readOnly(new ReadOnlySetterCallback(this))
    , editFinishEvt(this, &QLineEditEx::editingFinished)
    , returnPressEvt(this, &QLineEditEx::returnPressed)
    , textChangeEvt(this, &QLineEditEx::textChanged)
    , textEditEvt(this, &QLineEditEx::textEdited)
{
    connect(this, &QLineEdit::editingFinished, [&] {
        text.last() = text();
    });
}

void QLineEditEx::setRegExpression(const QString& reg) {
    if (regExpStr != reg) {
        regExpStr = reg;
        setValidator(new QRegExpValidator(QRegExp(reg), this));
    }
}
