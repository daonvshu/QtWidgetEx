﻿#pragma once

#include <qcombobox.h>

#include "interface/simpledatasetter.h"
#include "interface/listelementsetter.h"

#include "eventex/simpleeventex.h"

#include "utils/regexpwidget.h"

class QComboBoxEx : public RegExpWidget<QComboBox> {
    Q_OBJECT

    Q_PROPERTY(QString regExp READ getRegExp WRITE setRegExpression)

public:
    explicit QComboBoxEx(QWidget* parent = nullptr);

    _widget_ex::ListElementSetter items;
    _widget_ex::SimpleAsyncDataSetter<int> curIndex;
    _widget_ex::SimpleAsyncDataSetter<QString> curText;

    _widget_ex::SimpleEventEx<QComboBoxEx, int> curIndexChangeEvt;
    _widget_ex::SimpleEventEx<QComboBoxEx, const QString&> curTextChangeEvt;

    using QComboBox::setCompleter;
    void setCompleter();
    void setCompleter(const QStringList& wordList);
    void setCompleter(QAbstractItemModel* model);
};