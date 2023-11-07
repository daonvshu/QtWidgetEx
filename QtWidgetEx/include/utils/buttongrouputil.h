#pragma once

#include <qabstractbutton.h>
#include <functional>
#include <type_traits>

#include "../interface/simpledatasetter.h"

#include "../eventex/simpleeventex.h"

#include "exglobal.h"

EX_BEGIN_NAMESPACE
class IdSetterCallback;
class ExclusiveCallback;
EX_END_NAMESPACE

class QPushButton;
class ButtonGroupUtil : public QObject {
public:
    explicit ButtonGroupUtil(QAbstractButton* button);

    _widget_ex::SimpleAsyncDataSetter<int> id;
    _widget_ex::SimpleAsyncDataSetter<bool> exclusive;

    void operator+=(const std::function<void(bool)>& clickCallback);

#if (QT_VERSION >= QT_VERSION_CHECK(5, 15, 0))
    void operator+=(const std::function<void(int, bool)>& idClickCallback);
#endif

    QButtonGroup* operator()();

    template<typename T, typename... Args>
    void create(T* button, Args*... buttons) {
        Q_STATIC_ASSERT((std::is_base_of<QAbstractButton, T>::value));
        create(sizeof...(buttons) + 1, button, buttons...);
    }

    void setCancelableInGroup();

private:
    QAbstractButton* button;

    QAbstractButton* lastCheckButton = nullptr;
    bool cancelableInGroup = false;

    friend class _widget_ex::IdSetterCallback;
    friend class _widget_ex::ExclusiveCallback;

    void create(int size, ...);
};