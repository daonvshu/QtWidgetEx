#include "eventex/mouseeventex.h"

#include <qevent.h>

EX_BEGIN_NAMESPACE
enum PressType {
    LEFT_MOUSE_PRESS = 1,
    RIGHT_MOUSE_PRESS = 2,
    DOUBLE_CLICK = 4,
};

MouseEventEx::MouseEventEx(QWidget* parent)
    : QObject(parent)
    , pressType(LEFT_MOUSE_PRESS)
{
    parent->installEventFilter(this);
}

MouseEventEx& MouseEventEx::left(bool doubleClick) {
    pressType = LEFT_MOUSE_PRESS;
    if (doubleClick) {
        pressType |= DOUBLE_CLICK;
    }
    return *this;
}

MouseEventEx& MouseEventEx::right(bool doubleClick) {
    pressType = RIGHT_MOUSE_PRESS;
    if (doubleClick) {
        pressType |= DOUBLE_CLICK;
    }
    return *this;
}

void MouseEventEx::operator+=(const std::function<void()>& caller) {
    eventCaller << caller;
}

bool MouseEventEx::eventFilter(QObject* watched, QEvent* event) {
    if (watched == parent()) {
        auto mouseEvent = dynamic_cast<QMouseEvent*>(event);
        if (mouseEvent != nullptr && !eventCaller.isEmpty()) {
            if (mouseEvent->type() == QEvent::MouseButtonPress) {
                mousePressed = false;
                if (pressType == LEFT_MOUSE_PRESS) {
                    mousePressed = mouseEvent->button() == Qt::LeftButton;
                } else if (pressType == RIGHT_MOUSE_PRESS) {
                    mousePressed = mouseEvent->button() == Qt::RightButton;
                }
            } else if (mouseEvent->type() == QEvent::MouseMove) {
                mousePressed = false;
            } else if (mouseEvent->type() == QEvent::MouseButtonDblClick) {
                mousePressed = false;
                if (pressType & DOUBLE_CLICK) {
                    if (pressType & LEFT_MOUSE_PRESS) {
                        mousePressed = mouseEvent->button() == Qt::LeftButton;
                    } else if (pressType & RIGHT_MOUSE_PRESS) {
                        mousePressed = mouseEvent->button() == Qt::RightButton;
                    }
                }
            } else if (mouseEvent->type() == QEvent::MouseButtonRelease) {
                if (mousePressed) {
                    for (const auto& caller: eventCaller) {
                        caller();
                    }
                }
                mousePressed = false;
            }
            return true;
        }
    }
    return QObject::eventFilter(watched, event);
}
EX_END_NAMESPACE