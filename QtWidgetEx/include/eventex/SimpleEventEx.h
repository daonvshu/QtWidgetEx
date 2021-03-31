#pragma once

#include <qobject.h>
#include <functional>

template<typename T, typename... P>
class SimpleEventEx {
public:
    typedef void(T::*Signal)(P...);

    explicit SimpleEventEx(T* parent, Signal signal)
        : parent(parent)
        , parentSignal(signal)
        , type(Qt::AutoConnection)
    {}

    SimpleEventEx& connectType(Qt::ConnectionType type) {
        this->type = type;
        return *this;
    }

    void operator+=(const std::function<void(P...)>& caller) {
        QObject::connect(parent, parentSignal, caller);
    }

    template<typename K, typename Fun>
    SimpleEventEx& add(K* k, Fun slot);

private:
    T* parent;
    Signal parentSignal;

    Qt::ConnectionType type;
};

template<typename T, typename ...P>
template<typename K, typename Fun>
inline SimpleEventEx<T, P...>& SimpleEventEx<T, P...>::add(K* k, Fun slot) {
    QObject::connect(parent, parentSignal, k, slot, type);
    return *this;
}
