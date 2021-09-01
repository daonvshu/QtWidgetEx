#pragma once

#include <qlineedit.h>

#include "interface/textsetterinterface.h"
#include "interface/simpledatasetter.h"

#include "eventex/simpleeventex.h"

#include "utils/regexpwidget.h"

class QLineEditEx : public RegExpWidget<QLineEdit> {
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
};