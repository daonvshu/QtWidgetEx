#pragma once

#include "exglobal.h"

#include <qobject.h>
#include <qstandarditemmodel.h>

#include "interface/simpledatasetter.h"

EX_BEGIN_NAMESPACE

class ElementVariantDataSetter : public SimpleAsyncDataSetter<QVariant> {
public:
    using SimpleAsyncDataSetter<QVariant>::SimpleAsyncDataSetter;
    using SimpleAsyncDataSetter<QVariant>::operator=;

private:
    void setDataRole(int role) const;

    friend class ListElementSetter;
};

class ListElement: public QObject {
public:
    ListElement(QStandardItemModel* model, int rowIndex, int role = Qt::UserRole);

    SimpleAsyncDataSetter<QString> text;
    SimpleAsyncDataSetter<QIcon> icon;
    ElementVariantDataSetter data;

    ListElement& setText(const QString& text);
    ListElement& setIcon(const QIcon& icon);
    ListElement& setData(const QVariant& data);

private:
    int rowIndex;
    QStandardItemModel* model;

    template<typename T>
    friend class ModelItemDataSetterCallback;

    friend class ListElementSetter;
};

class ListElementSetter: public QObject {
public:
    explicit ListElementSetter(QObject* parent = nullptr);

    template<typename T>
    void attach(T* modelWidget) {
        modelWidget->setModel(model);
    }

    ListElementSetter& operator<<(const QString& text);

    ListElement& operator()(int index, int dataRole = Qt::UserRole);

    void insert(int index, const QString& text) const;
    void insert(int index, const QVariant& data, int dataRole = Qt::UserRole) const;
    void remove(int index) const;

    int size() const;

    QStandardItemModel* model;

private:
    ListElement element;
};

EX_END_NAMESPACE