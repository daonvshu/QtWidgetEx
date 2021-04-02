#include "QLabelExPlugin.h"
#include "QLabelEx.h"

#include <QtCore/QtPlugin>

QLabelExPlugin::QLabelExPlugin(QObject* parent)
    : QObject(parent) {
    initialized = false;
}

void QLabelExPlugin::initialize(QDesignerFormEditorInterface* /*core*/) {
    if (initialized)
        return;

    initialized = true;
}

bool QLabelExPlugin::isInitialized() const {
    return initialized;
}

QWidget* QLabelExPlugin::createWidget(QWidget* parent) {
    return new QLabelEx(parent);
}

QString QLabelExPlugin::name() const {
    return "QLabelEx";
}

QString QLabelExPlugin::group() const {
    return "Display Widgets";
}

QIcon QLabelExPlugin::icon() const {
    return QIcon(":/qt-wigetex/formeditor/images/widgets/label.png");
}

QString QLabelExPlugin::toolTip() const {
    return QString();
}

QString QLabelExPlugin::whatsThis() const {
    return QString();
}

bool QLabelExPlugin::isContainer() const {
    return false;
}

QString QLabelExPlugin::domXml() const {
    return "<widget class=\"QLabelEx\" name=\"labelEx\">\n"
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>54</width>\n"
        "   <height>12</height>\n"
        "  </rect>\n"
        " </property>\n"
        " <property name=\"text\">\n"
        "  <string>LabelEx</string>\n"
        " </property>\n"
        "</widget>\n";
}

QString QLabelExPlugin::includeFile() const {
    return "QLabelEx.h";
}
