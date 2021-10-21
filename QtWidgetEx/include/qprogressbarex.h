#pragma once

#include <qprogressbar.h>

#include "qprogressbarex.h"
#include "interface/simpledatasetter.h"

class QProgressBarEx : public QProgressBar
{
    Q_OBJECT

public:
    explicit QProgressBarEx(QWidget* parent = nullptr);

    _widget_ex::SimpleAsyncDataSetter<int> value;

    bool updateImmediately;
};