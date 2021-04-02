#pragma once

#include <qwidget.h>
#include <functional>

#include "../exglobal.h"

EX_BEGIN_NAMESPACE
class MouseEventEx: QObject {
public:
    explicit MouseEventEx(QWidget* parent);

    MouseEventEx& left(bool doubleClick = false); //default
    MouseEventEx& right(bool doubleClick = false);

    void operator+=(const std::function<void()>& caller);

    template<typename T>
    MouseEventEx& add(T* t, void(T::*caller)()) {
        eventCaller << [=] {
            (t->*caller)();
        };
        return *this;
    }

protected:
    bool eventFilter(QObject* watched, QEvent* event) override;

private:
    enum PressType {
        LEFT_MOUSE_PRESS = 1,
        RIGHT_MOUSE_PRESS = 2,
        DOUBLE_CLICK = 4,
    };

    int pressType;
    bool mousePressed;

    QList<std::function<void()>> eventCaller;
};
EX_END_NAMESPACE