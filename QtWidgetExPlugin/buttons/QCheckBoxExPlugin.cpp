#include "QCheckBoxExPlugin.h"
#include "QCheckBoxEx.h"

#include <QtCore/QtPlugin>

QCheckBoxExPlugin::QCheckBoxExPlugin(QObject* parent)
    : QObject(parent) {
    initialized = false;
}

void QCheckBoxExPlugin::initialize(QDesignerFormEditorInterface* /*core*/) {
    if (initialized)
        return;

    initialized = true;
}

bool QCheckBoxExPlugin::isInitialized() const {
    return initialized;
}

QWidget* QCheckBoxExPlugin::createWidget(QWidget* parent) {
    return new QCheckBoxEx(parent);
}

QString QCheckBoxExPlugin::name() const {
    return "QCheckBoxEx";
}

QString QCheckBoxExPlugin::group() const {
    return "Buttons";
}

QIcon QCheckBoxExPlugin::icon() const {
    return QIcon(":/qt-wigetex/formeditor/images/widgets/checkbox.png");
}

QString QCheckBoxExPlugin::toolTip() const {
    return QString();
}

QString QCheckBoxExPlugin::whatsThis() const {
    return QString();
}

bool QCheckBoxExPlugin::isContainer() const {
    return false;
}

QString QCheckBoxExPlugin::domXml() const {
    return "<widget class=\"QCheckBoxEx\" name=\"checkboxEx\">\n"
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>71</width>\n"
        "   <height>16</height>\n"
        "  </rect>\n"
        " </property>\n"
        " <property name=\"text\">\n"
        "  <string>CheckBoxEx</string>\n"
        " </property>\n"
        "</widget>\n";
}

QString QCheckBoxExPlugin::includeFile() const {
    return "QCheckBoxEx.h";
}
