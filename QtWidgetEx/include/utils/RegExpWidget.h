#pragma once

#include <qobject.h>
#include <qvalidator.h>

class RegExpWidgetImpl {
public:
    virtual void setRegValidator(QValidator* validator) = 0;

    void setRegExpression(const QString& reg);
    QString getRegExp() const;

private:
    QString regExpStr;
};

template<typename E>
class RegExpWidget : public E, public RegExpWidgetImpl {
public:
    using E::E;

    void setRegValidator(QValidator* validator) override {
        validator->setParent(this);
        setValidator(validator);
    }
};

