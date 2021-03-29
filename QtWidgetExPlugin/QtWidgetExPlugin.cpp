#include "QtWidgetExPlugin.h"

#include "display/QLabelExPlugin.h"

QtWidgetExPlugin::QtWidgetExPlugin(QObject* parent)
    : QObject(parent)
{
    widgets << new QLabelExPlugin(this);
}

QList<QDesignerCustomWidgetInterface*> QtWidgetExPlugin::customWidgets() const {
    return widgets;
}
