﻿#include "QToolButtonEx.h"

QToolButtonEx::QToolButtonEx(QWidget* parent)
    : QAbstractButtonEx<QToolButton>(parent)
    , triggerEvt(this, &QToolButton::triggered)
{}
