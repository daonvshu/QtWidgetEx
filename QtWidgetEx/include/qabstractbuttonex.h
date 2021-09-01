#pragma once

#include "interface/textsetterinterface.h"
#include "interface/iconsetterinterface.h"

#include "eventex/simpleeventex.h"

#include "utils/buttongrouputil.h"

EX_BEGIN_NAMESPACE
template<typename T>
class CheckStateSetterCallback : public SimpleDataTargetSetterCallback<bool, T> {
public:
    using SimpleDataTargetSetterCallback<bool, T>::SimpleDataTargetSetterCallback;

    void setData(const bool& checked) override {
        SimpleDataTargetSetterCallback<bool, T>::target->setChecked(checked);
    }

    bool getData() override {
        return SimpleDataTargetSetterCallback<bool, T>::target->isChecked();
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
        T::setIcon(icon);
        if (resize) {
            T::setIconSize(size);
        }
    }
};
