#include "qradiobuttonexplugin.h"
#include "qradiobuttonex.h"

#include <QtCore/QtPlugin>

QRadioButtonExPlugin::QRadioButtonExPlugin(QObject* parent)
    : QObject(parent) {
    initialized = false;
}

void QRadioButtonExPlugin::initialize(QDesignerFormEditorInterface* /*core*/) {
    if (initialized)
        return;

    initialized = true;
}

bool QRadioButtonExPlugin::isInitialized() const {
    return initialized;
}

QWidget* QRadioButtonExPlugin::createWidget(QWidget* parent) {
    return new QRadioButtonEx(parent);
}

QString QRadioButtonExPlugin::name() const {
    return "QRadioButtonEx";
}

QString QRadioButtonExPlugin::group() const {
    return "Buttons";
}

QIcon QRadioButtonExPlugin::icon() const {
    return QIcon(":/qt-wigetex/formeditor/images/widgets/radiobutton.png");
}

QString QRadioButtonExPlugin::toolTip() const {
    return QString();
}

QString QRadioButtonExPlugin::whatsThis() const {
    return QString();
}

bool QRadioButtonExPlugin::isContainer() const {
    return false;
}

QString QRadioButtonExPlugin::domXml() const {
    return "<widget class=\"QRadioButtonEx\" name=\"radiobuttonEx\">\n"
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>100</width>\n"
        "   <height>16</height>\n"
        "  </rect>\n"
        " </property>\n"
        " <property name=\"text\">\n"
        "  <string>RadioButtonEx</string>\n"
        " </property>\n"
        "</widget>\n";
}

QString QRadioButtonExPlugin::includeFile() const {
    return "qradiobuttonex.h";
}
