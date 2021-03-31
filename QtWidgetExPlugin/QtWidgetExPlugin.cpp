#include "QtWidgetExPlugin.h"

#include "display/QLabelExPlugin.h"

#include "buttons/QPushButtonExPlugin.h"

QtWidgetExPlugin::QtWidgetExPlugin(QObject* parent)
    : QObject(parent)
{
    widgets << new QLabelExPlugin(this);
    widgets << new QPushButtonExPlugin(this);
}

QList<QDesignerCustomWidgetInterface*> QtWidgetExPlugin::customWidgets() const {
    return widgets;
}
