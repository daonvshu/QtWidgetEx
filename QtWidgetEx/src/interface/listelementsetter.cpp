﻿#include "interface/listelementsetter.h"

EX_BEGIN_NAMESPACE
ListElementSetter::ListElementSetter(QObject* parent)
    : QObject(parent)
    , model(new QStandardItemModel(this))
    , element(model, 0)
{
}

ListElementSetter& ListElementSetter::operator<<(const QString& text) {
    model->appendRow(new QStandardItem(text));
    return *this;
}

ListElement& ListElementSetter::operator()(int index, int role) {
    element.rowIndex = index;
    element.data.setDataRole(role);
    return element;
}

void ListElementSetter::insert(int index, const QString& text) const {
    model->insertRow(index, new QStandardItem(text));
}

void ListElementSetter::insert(int index, const QVariant& data, int dataRole) const {
    auto item = new QStandardItem;
    item->setData(data, dataRole);
    model->insertRow(index, item);
}

void ListElementSetter::remove(int index) const {
    model->removeRow(index);
}

int ListElementSetter::size() const {
    return model->rowCount();
}

template<typename T>
class ModelItemDataSetterCallback : public SimpleDataTargetSetterCallback<T, ListElement> {
public:
    explicit ModelItemDataSetterCallback(ListElement* element, int role)
        : SimpleDataTargetSetterCallback<T, ListElement>(element)
        , dataRole(role)
    {}

    void setData(const T& data) override {
        QStandardItemModel* model = SimpleDataTargetSetterCallback<T, ListElement>::target->model;
        QModelIndex item = model->index(SimpleDataTargetSetterCallback<T, ListElement>::target->rowIndex, 0);
        if (item.isValid()) {
            model->setData(item, data, dataRole);
        }
    }

    T getData() override {
        QStandardItemModel* model = SimpleDataTargetSetterCallback<T, ListElement>::target->model;
        QModelIndex item = model->index(SimpleDataTargetSetterCallback<T, ListElement>::target->rowIndex, 0);
        return item.data(dataRole).value<T>();
    }

private:
    int dataRole;

    friend class ListElementSetter;
    friend class ElementVariantDataSetter;
};

void ElementVariantDataSetter::setDataRole(int role) const {
    dynamic_cast<ModelItemDataSetterCallback<QVariant>*>(callback)->dataRole = role;
}

ListElement::ListElement(QStandardItemModel* model, int rowIndex, int role)
    : QObject(model)
    , text(new ModelItemDataSetterCallback<QString>(this, Qt::DisplayRole))
    , icon(new ModelItemDataSetterCallback<QIcon>(this, Qt::DecorationRole))
    , data(new ModelItemDataSetterCallback<QVariant>(this, role))
    , rowIndex(rowIndex)
    , model(model)
{
}

ListElement& ListElement::setText(const QString& text) {
    this->text = text;
    return *this;
}

ListElement& ListElement::setIcon(const QIcon& icon) {
    this->icon = icon;
    return *this;
}

ListElement& ListElement::setData(const QVariant& data) {
    this->data = data;
    return *this;
}

EX_END_NAMESPACE


