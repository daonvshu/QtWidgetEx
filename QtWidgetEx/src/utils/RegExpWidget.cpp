#include "utils/RegExpWidget.h"

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

void RegExpWidgetImpl::setRegExpression(const QString& reg) {
    if (regExpStr != reg) {
        regExpStr = reg;
        do {
            //like "-int(-1,100)", min -> -1 max -> 100
            if (reg.startsWith("-int")) {
                QRegExp rx("(-?\\d+)");
                QStringList list;
                int pos = 0;

                while ((pos = rx.indexIn(reg, pos)) != -1) {
                    list << rx.cap(1);
                    pos += rx.matchedLength();
                }

                if (list.size() >= 2) {
                    setRegValidator(new MyIntValidator(list[0].toInt(), list[1].toInt()));
                    break;
                }
            } else if (reg.startsWith("-double")) {
                QRegExp rx("(-?\\d+(\\.\\d+)?)");
                QStringList list;
                int pos = 0;

                while ((pos = rx.indexIn(reg, pos)) != -1) {
                    list << rx.cap(1);
                    pos += rx.matchedLength();
                }

                if (list.size() >= 2) {
                    auto validator = new MyDoubleValidator;
                    if (list.size() > 2) {
                        validator->setRange(list[0].toDouble(), list[1].toDouble(), list[2].toInt());
                    } else {
                        validator->setRange(list[0].toDouble(), list[1].toDouble());
                    }
                    setRegValidator(validator);
                    break;
                }
            }
            setRegValidator(new QRegExpValidator(QRegExp(reg)));
        } while (0);
    }
}

QString RegExpWidgetImpl::getRegExp() const {
    return regExpStr;
}
