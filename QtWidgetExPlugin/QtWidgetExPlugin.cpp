#include "QtWidgetExPlugin.h"

#include "display/QLabelExPlugin.h"

#include "buttons/QPushButtonExPlugin.h"
#include "buttons/QCheckBoxExPlugin.h"

#include "input/QComboBoxExPlugin.h"
#include "input/QLineEditExPlugin.h"

QtWidgetExPlugin::QtWidgetExPlugin(QObject* parent)
    : QObject(parent)
{
    widgets << new QLabelExPlugin(this);

    widgets << new QPushButtonExPlugin(this);
    widgets << new QCheckBoxExPlugin(this);

    widgets << new QComboBoxExPlugin(this);
    widgets << new QLineEditExPlugin(this);
}

QList<QDesignerCustomWidgetInterface*> QtWidgetExPlugin::customWidgets() const {
    return widgets;
}
