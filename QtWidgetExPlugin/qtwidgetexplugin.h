#pragma once

#include <QtCore/qplugin.h>
#include <QtUiPlugin/QDesignerCustomWidgetInterface>

class QtWidgetExPlugin : public QObject, public QDesignerCustomWidgetCollectionInterface {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetCollectionInterface")
    Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)

public:
    QtWidgetExPlugin(QObject* parent = 0);

    QList<QDesignerCustomWidgetInterface*> customWidgets() const override;

private:
    QList<QDesignerCustomWidgetInterface*> widgets;
};