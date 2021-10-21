#include "qtwidgetexplugin.h"

#include "display/qlabelexplugin.h"
#include "display/qprogressbarexplugin.h"

#include "buttons/qpushbuttonexplugin.h"
#include "buttons/qcheckboxexplugin.h"
#include "buttons/qradiobuttonexplugin.h"
#include "buttons/qtoolbuttonexplugin.h"

#include "input/qcomboboxexplugin.h"
#include "input/qlineeditexplugin.h"

QtWidgetExPlugin::QtWidgetExPlugin(QObject* parent)
    : QObject(parent)
{
    widgets << new QLabelExPlugin(this);
    widgets << new QProgressBarExPlugin(this);

    widgets << new QPushButtonExPlugin(this);
    widgets << new QCheckBoxExPlugin(this);
    widgets << new QRadioButtonExPlugin(this);
    widgets << new QToolButtonExPlugin(this);

    widgets << new QComboBoxExPlugin(this);
    widgets << new QLineEditExPlugin(this);
}

QList<QDesignerCustomWidgetInterface*> QtWidgetExPlugin::customWidgets() const {
    return widgets;
}
