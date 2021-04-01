#pragma once

#include <qpushbutton.h>

#include "interface/TextSetterInterface.h"

#include "eventex/SimpleEventEx.h"

class QPushButtonEx : public QPushButton {
    Q_OBJECT

public:
    explicit QPushButtonEx(QWidget* parent = nullptr);
    explicit QPushButtonEx(const QString& text, QWidget* parent = nullptr);
    QPushButtonEx(const QIcon& icon, const QString& text, QWidget* parent = nullptr);

    _widget_ex::SimpleEventEx<QPushButtonEx, bool> clickEvt;
    _widget_ex::SimpleEventEx<QPushButtonEx> pressEvt;
    _widget_ex::SimpleEventEx<QPushButtonEx> releaseEvt;
    _widget_ex::SimpleEventEx<QPushButtonEx, bool> toggleEvt;

    _widget_ex::TextSetterInterface text;
};