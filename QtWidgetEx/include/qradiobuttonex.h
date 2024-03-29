﻿#pragma once

#include <qradiobutton.h>

#include "qabstractbuttonex.h"

class QRadioButtonEx : public QAbstractButtonEx<QRadioButton> {
    Q_OBJECT

public:
    using QAbstractButtonEx::QAbstractButtonEx;

    explicit QRadioButtonEx(const QString& text, QWidget* parent = nullptr);
};