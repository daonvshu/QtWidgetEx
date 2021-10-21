#include "qprogressbarex.h"

EX_BEGIN_NAMESPACE
class ProgressValueSetterCallback : public SimpleDataTargetSetterCallback<int, QProgressBarEx> {
public:
    using SimpleDataTargetSetterCallback::SimpleDataTargetSetterCallback;

    void setData(const int& value) override {
        target->setValue(value);
        if (target->updateImmediately) {
            target->update();
        }
    }

    int getData() override {
        return target->QProgressBar::value();
    }
};
EX_END_NAMESPACE

QProgressBarEx::QProgressBarEx(QWidget* parent)
    : QProgressBar(parent)
    , value(new _widget_ex::ProgressValueSetterCallback(this))
    , updateImmediately(false)
{
    
}
