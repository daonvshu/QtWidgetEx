#pragma once

#include <qlineedit.h>

#include "interface/TextSetterInterface.h"
#include "interface/SimpleDataSetter.h"

#include "eventex/SimpleEventEx.h"

class QLineEditEx : public QLineEdit {
    Q_OBJECT

    Q_PROPERTY(QString regExp READ getRegExp WRITE setRegExpression)

public:
    explicit QLineEditEx(QWidget* parent = nullptr);
    explicit QLineEditEx(const QString&, QWidget* parent = nullptr);

    _widget_ex::TextSetterInterface text;
    _widget_ex::SimpleAsyncDataSetter<bool> readOnly;

    _widget_ex::SimpleEventEx<QLineEditEx> editFinishEvt;
    _widget_ex::SimpleEventEx<QLineEditEx> returnPressEvt;
    _widget_ex::SimpleEventEx2<QLineEditEx, QString> textChangeEvt;
    _widget_ex::SimpleEventEx2<QLineEditEx, QString> textEditEvt;

    QString getRegExp() const {
        return regExpStr;
    }

    void setRegExpression(const QString& reg);

private:
    QString regExpStr;
};