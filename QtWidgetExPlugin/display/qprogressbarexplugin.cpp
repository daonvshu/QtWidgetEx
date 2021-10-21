#include "qprogressbarexplugin.h"
#include "qprogressbarex.h"

#include <QtCore/QtPlugin>

QProgressBarExPlugin::QProgressBarExPlugin(QObject* parent)
    : QObject(parent) {
    initialized = false;
}

void QProgressBarExPlugin::initialize(QDesignerFormEditorInterface* /*core*/) {
    if (initialized)
        return;

    initialized = true;
}

bool QProgressBarExPlugin::isInitialized() const {
    return initialized;
}

QWidget* QProgressBarExPlugin::createWidget(QWidget* parent) {
    return new QProgressBarEx(parent);
}

QString QProgressBarExPlugin::name() const {
    return "QProgressBarEx";
}

QString QProgressBarExPlugin::group() const {
    return "Display Widgets";
}

QIcon QProgressBarExPlugin::icon() const {
    return QIcon(":/qt-wigetex/formeditor/images/widgets/progress.png");
}

QString QProgressBarExPlugin::toolTip() const {
    return QString();
}

QString QProgressBarExPlugin::whatsThis() const {
    return QString();
}

bool QProgressBarExPlugin::isContainer() const {
    return false;
}

QString QProgressBarExPlugin::domXml() const {
    return "<widget class=\"QProgressBarEx\" name=\"qprogressbarEx\">\n"
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>118</width>\n"
        "   <height>23</height>\n"
        "  </rect>\n"
        " </property>\n"
        " <property name=\"value\">\n"
        "  <string>24</string>\n"
        " </property>\n"
        "</widget>\n";
}

QString QProgressBarExPlugin::includeFile() const {
    return "qprogressbarex.h";
}
