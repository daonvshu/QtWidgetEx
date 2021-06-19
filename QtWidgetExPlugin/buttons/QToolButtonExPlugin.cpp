#include "QToolButtonExPlugin.h"
#include "QToolButtonEx.h"

#include <QtCore/QtPlugin>

QToolButtonExPlugin::QToolButtonExPlugin(QObject* parent)
    : QObject(parent) {
    initialized = false;
}

void QToolButtonExPlugin::initialize(QDesignerFormEditorInterface* /*core*/) {
    if (initialized)
        return;

    initialized = true;
}

bool QToolButtonExPlugin::isInitialized() const {
    return initialized;
}

QWidget* QToolButtonExPlugin::createWidget(QWidget* parent) {
    return new QToolButtonEx(parent);
}

QString QToolButtonExPlugin::name() const {
    return "QToolButtonEx";
}

QString QToolButtonExPlugin::group() const {
    return "Buttons";
}

QIcon QToolButtonExPlugin::icon() const {
    return QIcon(":/qt-wigetex/formeditor/images/widgets/toolbutton.png");
}

QString QToolButtonExPlugin::toolTip() const {
    return QString();
}

QString QToolButtonExPlugin::whatsThis() const {
    return QString();
}

bool QToolButtonExPlugin::isContainer() const {
    return false;
}

QString QToolButtonExPlugin::domXml() const {
    return "<widget class=\"QToolButtonEx\" name=\"toolbuttonEx\">\n"
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>90</width>\n"
        "   <height>18</height>\n"
        "  </rect>\n"
        " </property>\n"
        " <property name=\"text\">\n"
        "  <string>ToolButtonEx</string>\n"
        " </property>\n"
        "</widget>\n";
}

QString QToolButtonExPlugin::includeFile() const {
    return "QToolButtonEx.h";
}
