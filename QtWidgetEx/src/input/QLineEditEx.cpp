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

class MyIntValidator : public QIntValidator {
public:
    using QIntValidator::QIntValidator;

    State validate(QString& str, int& i) const override {
        auto state = QIntValidator::validate(str, i);
        if (str.isEmpty() || str == "-") {
            return state;
        }
        return state == QValidator::Acceptable ? state : QValidator::Invalid;
    }
};

class MyDoubleValidator : public QDoubleValidator {
public:
    using QDoubleValidator::QDoubleValidator;

    State validate(QString& str, int& i) const override {
        auto state = QDoubleValidator::validate(str, i);
        if (str.isEmpty() || str == "-") {
            return state;
        }
        return state == QValidator::Acceptable ? state : QValidator::Invalid;
    }
};

void QLineEditEx::setRegExpression(const QString& reg) {
    if (regExpStr != reg) {
        regExpStr = reg;
        do {
            //like "-int(-1,100)", min -> -1 max -> 100
            if (reg.startsWith("-int") || reg.startsWith("-double")) {
                QRegExp rx("(int|double|-?\\d+)");
                QStringList list;
                int pos = 0;

                while ((pos = rx.indexIn(reg, pos)) != -1) {
                    list << rx.cap(1);
                    pos += rx.matchedLength();
                }

                if (list[0] == "int") {
                    if (list.size() >= 3) {
                        setValidator(new MyIntValidator(list[1].toInt(), list[2].toInt(), this));
                        break;
                    }
                } else if (list[0] == "double") {
                    if (list.size() >= 3) {
                        auto validator = new MyDoubleValidator(this);
                        if (list.size() > 3) {
                            validator->setRange(list[1].toDouble(), list[2].toDouble(), list[3].toInt());
                        } else {
                            validator->setRange(list[1].toDouble(), list[2].toDouble());
                        }
                        setValidator(validator);
                        break;
                    }
                }
            }
            setValidator(new QRegExpValidator(QRegExp(reg), this));
        } while (0);
    }
}
