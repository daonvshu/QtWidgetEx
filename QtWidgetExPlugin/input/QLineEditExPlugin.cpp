#include "QLineEditExPlugin.h"
#include "QLineEditEx.h"

#include <QtCore/QtPlugin>

QLineEditExPlugin::QLineEditExPlugin(QObject* parent)
    : QObject(parent) {
    initialized = false;
}

void QLineEditExPlugin::initialize(QDesignerFormEditorInterface* /*core*/) {
    if (initialized)
        return;

    initialized = true;
}

bool QLineEditExPlugin::isInitialized() const {
    return initialized;
}

QWidget* QLineEditExPlugin::createWidget(QWidget* parent) {
    return new QLineEditEx(parent);
}

QString QLineEditExPlugin::name() const {
    return "QLineEditEx";
}

QString QLineEditExPlugin::group() const {
    return "Input Widgets";
}

QIcon QLineEditExPlugin::icon() const {
    return QIcon(":/qt-wigetex/formeditor/images/widgets/lineedit.png");
}

QString QLineEditExPlugin::toolTip() const {
    return QString();
}

QString QLineEditExPlugin::whatsThis() const {
    return QString();
}

bool QLineEditExPlugin::isContainer() const {
    return false;
}

QString QLineEditExPlugin::domXml() const {
    return "<widget class=\"QLineEditEx\" name=\"lineeditex\">\n"
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>113</width>\n"
        "   <height>20</height>\n"
        "  </rect>\n"
        " </property>\n"
        "</widget>\n";
}

QString QLineEditExPlugin::includeFile() const {
    return "QLineEditEx.h";
}
