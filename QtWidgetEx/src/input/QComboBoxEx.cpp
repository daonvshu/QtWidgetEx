#include "QComboBoxEx.h"

EX_BEGIN_NAMESPACE
class ItemsSetterCallback : public SimpleDataTargetSetterCallback<QStringList, QComboBox> {
public:
    using SimpleDataTargetSetterCallback::SimpleDataTargetSetterCallback;

    void setData(const QStringList& items) override {
        target->clear();
        target->addItems(items);
    }

    QStringList getData() override {
        QStringList text;
        for (int i=0; i<target->count(); i++) {
            text << target->itemText(i);
        }
        return text;
    }
};

class CurrentIndexSetterCallback : public SimpleDataTargetSetterCallback<int, QComboBox> {
public:
    using SimpleDataTargetSetterCallback::SimpleDataTargetSetterCallback;

    void setData(const int& i) override {
        target->setCurrentIndex(i);
    }

    int getData() override {
        return target->currentIndex();
    }
};

class CurrentTextSetterCallback : public SimpleDataTargetSetterCallback<QString, QComboBox> {
public:
    using SimpleDataTargetSetterCallback::SimpleDataTargetSetterCallback;

    void setData(const QString& text) override {
        target->setCurrentText(text);
    }

    QString getData() override {
        return target->currentText();
    }
};
EX_END_NAMESPACE

EX_USING_NAMESPACE
QComboBoxEx::QComboBoxEx(QWidget* parent)
    : RegExpWidget<QComboBox>(parent)
    , items(new ItemsSetterCallback(this))
    , curIndex(new CurrentIndexSetterCallback(this))
    , curText(new CurrentTextSetterCallback(this))
    , curIndexChangeEvt(this, &QComboBoxEx::currentIndexChanged)
    , curTextChangeEvt(this, &QComboBoxEx::currentTextChanged)
{
    
}
