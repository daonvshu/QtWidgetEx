#include "QPushButtonExPlugin.h"
#include "QPushButtonEx.h"

#include <QtCore/QtPlugin>

QPushButtonExPlugin::QPushButtonExPlugin(QObject* parent)
    : QObject(parent) {
    initialized = false;
}

void QPushButtonExPlugin::initialize(QDesignerFormEditorInterface* /*core*/) {
    if (initialized)
        return;

    initialized = true;
}

bool QPushButtonExPlugin::isInitialized() const {
    return initialized;
}

QWidget* QPushButtonExPlugin::createWidget(QWidget* parent) {
    return new QPushButtonEx(parent);
}

QString QPushButtonExPlugin::name() const {
    return "QPushButtonEx";
}

QString QPushButtonExPlugin::group() const {
    return "Buttons";
}

QIcon QPushButtonExPlugin::icon() const {
    return QIcon(":/qt-wigetex/formeditor/images/widgets/pushbutton.png");
}

QString QPushButtonExPlugin::toolTip() const {
    return QString();
}

QString QPushButtonExPlugin::whatsThis() const {
    return QString();
}

bool QPushButtonExPlugin::isContainer() const {
    return false;
}

QString QPushButtonExPlugin::domXml() const {
    return "<widget class=\"QPushButtonEx\" name=\"pushButtonEx\">\n"
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>75</width>\n"
        "   <height>23</height>\n"
        "  </rect>\n"
        " </property>\n"
        "</widget>\n";
}

QString QPushButtonExPlugin::includeFile() const {
    return "QPushButtonEx.h";
}
