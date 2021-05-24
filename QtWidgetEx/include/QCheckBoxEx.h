#pragma once

#include <qcheckbox.h>

#include "QAbstractButtonEx.h"

class QCheckBoxEx : public QAbstractButtonEx<QCheckBox> {
    Q_OBJECT

public:
    explicit QCheckBoxEx(QWidget* parent = nullptr);
    explicit QCheckBoxEx(const QString& text, QWidget* parent = nullptr);

    _widget_ex::SimpleAsyncDataSetter<Qt::CheckState> state;

    _widget_ex::SimpleEventEx<QCheckBox, int> stateEvt;
};