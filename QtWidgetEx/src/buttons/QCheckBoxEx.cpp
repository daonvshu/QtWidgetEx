#include "QCheckBoxEx.h"

#include "exglobal.h"

EX_BEGIN_NAMESPACE
class CheckBoxStateSetterCallback : public SimpleDataTargetSetterCallback<Qt::CheckState, QCheckBox> {
public:
    using SimpleDataTargetSetterCallback::SimpleDataTargetSetterCallback;

    void setData(const Qt::CheckState& state) override {
        target->setCheckState(state);
    }

    Qt::CheckState getData() override {
        return target->checkState();
    }
};
EX_END_NAMESPACE

QCheckBoxEx::QCheckBoxEx(QWidget* parent) : QCheckBoxEx(QString(), parent) {}

QCheckBoxEx::QCheckBoxEx(const QString& text, QWidget* parent)
    : QAbstractButtonEx<QCheckBox>(parent)
    , state(new _widget_ex::CheckBoxStateSetterCallback(this))
    , stateEvt(this, &QCheckBox::stateChanged)
{
    this->text = text;
}

