#pragma once

#include <qpushbutton.h>

#include "interface/TextSetterInterface.h"

#include "eventex/SimpleEventEx.h"

class QPushButtonEx : public QPushButton, TextSetterCallback {
    Q_OBJECT

public:
    explicit QPushButtonEx(QWidget* parent = nullptr);
    explicit QPushButtonEx(const QString& text, QWidget* parent = nullptr);
    QPushButtonEx(const QIcon& icon, const QString& text, QWidget* parent = nullptr);

    SimpleEventEx<QPushButtonEx, bool> clickEvt;
    SimpleEventEx<QPushButtonEx> pressEvt;
    SimpleEventEx<QPushButtonEx> releaseEvt;
    SimpleEventEx<QPushButtonEx, bool> toggleEvt;

    TextSetterInterface text;

protected:
    void setTextSync(const QString&) override;
};