#include "utils/regexpwidget.h"

#include <qregularexpression.h>

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
                QStringList list;

                static QRegularExpression rx(R"(-?\d+)");
                auto it = rx.globalMatch(reg);
                while (it.hasNext()) {
                    list << it.next().captured(1);
                }

                if (list.size() >= 2) {
                    setRegValidator(new MyIntValidator(list[0].toInt(), list[1].toInt()));
                    break;
                }
            } else if (reg.startsWith("-double")) {
                static QRegularExpression rx(R"((-?\d+(\.\d+)?))");
                QStringList list;

                auto it = rx.globalMatch(reg);
                while (it.hasNext()) {
                    list << it.next().captured(1);
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
            setRegValidator(new QRegularExpressionValidator(QRegularExpression(reg)));
        } while (0);
    }
}

QString RegExpWidgetImpl::getRegExp() const {
    return regExpStr;
}
