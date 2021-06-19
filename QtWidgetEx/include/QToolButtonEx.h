#pragma once

#include <qtoolbutton.h>

#include "QAbstractButtonEx.h"

class QToolButtonEx : public QAbstractButtonEx<QToolButton> {
    Q_OBJECT

public:
    explicit QToolButtonEx(QWidget* parent = nullptr);

    _widget_ex::SimpleEventEx<QToolButton, QAction*> triggerEvt;
};