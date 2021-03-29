#pragma once

#include <qwidget.h>
#include <functional>

class MouseEventEx: QObject {
public:
    explicit MouseEventEx(QWidget* parent);

    MouseEventEx& left(bool doubleClick = false); //default
    MouseEventEx& right(bool doubleClick = false);

    void operator+=(const std::function<void()>& caller);

    template<typename T>
    MouseEventEx& addBinder(const T* t, const std::function<void(T*)>& memberCaller);

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

template<typename T>
inline MouseEventEx& MouseEventEx::addBinder(const T* t, const std::function<void(T*)>& memberCaller) {
    eventCaller << [=] {
        memberCaller(t);
    };
}
