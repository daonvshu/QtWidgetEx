#include "qcomboboxexplugin.h"
#include "qcomboboxex.h"

#include <QtCore/QtPlugin>

QComboBoxExPlugin::QComboBoxExPlugin(QObject* parent)
    : QObject(parent) {
    initialized = false;
}

void QComboBoxExPlugin::initialize(QDesignerFormEditorInterface* /*core*/) {
    if (initialized)
        return;

    initialized = true;
}

bool QComboBoxExPlugin::isInitialized() const {
    return initialized;
}

QWidget* QComboBoxExPlugin::createWidget(QWidget* parent) {
    return new QComboBoxEx(parent);
}

QString QComboBoxExPlugin::name() const {
    return "QComboBoxEx";
}

QString QComboBoxExPlugin::group() const {
    return "Input Widgets";
}

QIcon QComboBoxExPlugin::icon() const {
    return QIcon(":/qt-wigetex/formeditor/images/widgets/combobox.png");
}

QString QComboBoxExPlugin::toolTip() const {
    return QString();
}

QString QComboBoxExPlugin::whatsThis() const {
    return QString();
}

bool QComboBoxExPlugin::isContainer() const {
    return false;
}

QString QComboBoxExPlugin::domXml() const {
    return "<widget class=\"QComboBoxEx\" name=\"comboboxex\">\n"
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>69</width>\n"
        "   <height>22</height>\n"
        "  </rect>\n"
        " </property>\n"
        "</widget>\n";
}

QString QComboBoxExPlugin::includeFile() const {
    return "qcomboboxex.h";
}
