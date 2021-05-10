#pragma once

#include "exglobal.h"

#include <qobject.h>
#include <qstandarditemmodel.h>

#include "interface/SimpleDataSetter.h"

EX_BEGIN_NAMESPACE
class ListElementSetter;
class ListElement: public QObject {
public:
    ListElement(QStandardItemModel* model, int rowIndex, Qt::ItemDataRole role = Qt::UserRole);

    SimpleAsyncDataSetter<QString> text;
    SimpleAsyncDataSetter<QIcon> icon;
    SimpleAsyncDataSetter<QVariant> data;

    ListElement& setText(const QString& text);
    ListElement& setIcon(const QIcon& icon);
    ListElement& setData(const QVariant& data);

private:
    int rowIndex;
    QStandardItemModel* model;
    Qt::ItemDataRole dataRole;

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

    ListElement& operator()(int index, Qt::ItemDataRole dataRole = Qt::UserRole);

    void insert(int index, const QString& text);
    void remove(int index);

    int size() const;

    QStandardItemModel* model;

private:
    ListElement element;
};

EX_END_NAMESPACE