#pragma once

#include <QtWidgets/QWidget>
#include "ui_WidgetExTest.h"

class WidgetExTest : public QWidget
{
    Q_OBJECT

public:
    WidgetExTest(QWidget *parent = Q_NULLPTR);

    void initWidgetTree();

private:
    Ui::WidgetExTestClass ui;
};
