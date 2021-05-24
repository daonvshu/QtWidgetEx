#pragma once

#include "interface/TextSetterInterface.h"
#include "interface/IconSetterInterface.h"

#include "eventex/SimpleEventEx.h"

#include "utils/ButtonGroupUtil.h"

EX_BEGIN_NAMESPACE
template<typename T>
class CheckStateSetterCallback : public SimpleDataTargetSetterCallback<bool, T> {
public:
    using SimpleDataTargetSetterCallback::SimpleDataTargetSetterCallback;

    void setData(const bool& checked) override {
        target->setChecked(checked);
    }

    bool getData() override {
        return target->isChecked();
    }
};
EX_END_NAMESPACE

template<typename T>
class QAbstractButtonEx: public T, _widget_ex::IconSetterCallback {
public:
    _widget_ex::SimpleEventEx<T, bool> clickEvt;
    _widget_ex::SimpleEventEx<T> pressEvt;
    _widget_ex::SimpleEventEx<T> releaseEvt;
    _widget_ex::SimpleEventEx<T, bool> toggleEvt;

    _widget_ex::TextSetterInterface text;
    _widget_ex::IconSetterInterface icon;

    _widget_ex::SimpleAsyncDataSetter<bool> checked;

    ButtonGroupUtil group;

    explicit QAbstractButtonEx(QWidget* parent = nullptr)
        : T(parent)
        , clickEvt(this, &T::clicked)
        , pressEvt(this, &T::pressed)
        , releaseEvt(this, &T::released)
        , toggleEvt(this, &T::toggled)
        , text(new _widget_ex::TextSetterCallback<T>(this))
        , icon(this, this)
        , checked(new _widget_ex::CheckStateSetterCallback<T>(this))
        , group(this)
    {
    }

private:
    void setIconSync(const QIcon& icon, bool resize, const QSize& size) override {
        setIcon(icon);
        if (resize) {
            setIconSize(size);
        }
    }
};