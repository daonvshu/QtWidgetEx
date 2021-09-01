#include "interface/listelementsetter.h"

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

ListElement& ListElementSetter::operator()(int index, Qt::ItemDataRole role) {
    element.rowIndex = index;
    element.dataRole = role;
    return element;
}

void ListElementSetter::insert(int index, const QString& text) {
    model->insertRow(index, new QStandardItem(text));
}

void ListElementSetter::remove(int index) {
    model->removeRow(index);
}

int ListElementSetter::size() const {
    return model->rowCount();
}


template<typename T>
class ModelItemDataSetterCallback : public SimpleDataTargetSetterCallback<T, ListElement> {
public:
    explicit ModelItemDataSetterCallback(ListElement* element, Qt::ItemDataRole role)
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
    Qt::ItemDataRole dataRole;
};

ListElement::ListElement(QStandardItemModel* model, int rowIndex, Qt::ItemDataRole role)
    : QObject(model)
    , model(model)
    , rowIndex(rowIndex)
    , dataRole(role)
    , text(new ModelItemDataSetterCallback<QString>(this, Qt::DisplayRole))
    , icon(new ModelItemDataSetterCallback<QIcon>(this, Qt::DecorationRole))
    , data(new ModelItemDataSetterCallback<QVariant>(this, dataRole))
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


