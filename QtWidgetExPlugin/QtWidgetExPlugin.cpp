#include "QtWidgetExPlugin.h"

QtWidgetExPlugin::QtWidgetExPlugin(QObject* parent)
    : QObject(parent)
{
}

QList<QDesignerCustomWidgetInterface*> QtWidgetExPlugin::customWidgets() const {
    return widgets;
}
