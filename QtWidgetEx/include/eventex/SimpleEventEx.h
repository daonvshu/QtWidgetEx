#pragma once

#include <qobject.h>
#include <functional>

#include "../exglobal.h"

EX_BEGIN_NAMESPACE
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

    //qobject member function need
    template<typename K, typename Fun>
    SimpleEventEx& add(K* k, Fun slot) {
        QObject::connect(parent, parentSignal, k, slot, type);
        return *this;
    }

private:
    T* parent;
    Signal parentSignal;

    Qt::ConnectionType type;
};

template<typename T, typename... P>
class SimpleEventEx2 {
public:
    typedef void(T::* SignalConst)(const P&...);

    explicit SimpleEventEx2(T* parent, SignalConst signal)
        : parent(parent)
        , parentSignal(signal)
        , type(Qt::AutoConnection)
    {}

    SimpleEventEx2& connectType(Qt::ConnectionType type) {
        this->type = type;
        return *this;
    }

    void operator+=(const std::function<void(const P&...)>& caller) {
        QObject::connect(parent, parentSignal, caller);
    }

    template<typename K, typename Fun>
    SimpleEventEx2& add(K* k, Fun slot) {
        QObject::connect(parent, parentSignal, k, slot, type);
        return *this;
    }

private:
    T* parent;
    SignalConst parentSignal;

    Qt::ConnectionType type;
};
EX_END_NAMESPACE