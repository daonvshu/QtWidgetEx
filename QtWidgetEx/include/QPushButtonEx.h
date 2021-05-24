#pragma once

#include <qpushbutton.h>

#include "QAbstractButtonEx.h"

class QPushButtonEx : public QAbstractButtonEx<QPushButton> {
    Q_OBJECT

public:
    using QAbstractButtonEx::QAbstractButtonEx;

    explicit QPushButtonEx(const QString& text, QWidget* parent = nullptr);
    QPushButtonEx(const QIcon& icon, const QString& text, QWidget* parent = nullptr);
};