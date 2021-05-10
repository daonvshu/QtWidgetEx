#include "QComboBoxEx.h"

#include <qcompleter.h>

EX_BEGIN_NAMESPACE
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
    , curIndex(new CurrentIndexSetterCallback(this))
    , curText(new CurrentTextSetterCallback(this))
    , curIndexChangeEvt(this, &QComboBoxEx::currentIndexChanged)
    , curTextChangeEvt(this, &QComboBoxEx::currentTextChanged)
{
    items.attach(this);
}

void QComboBoxEx::setCompleter() {
    auto completer = new QCompleter(this);
    completer->setModel(items.model);
    setCompleter(completer);
}

void QComboBoxEx::setCompleter(const QStringList& wordList) {
    auto completer = new QCompleter(wordList, this);
    setCompleter(completer);
}

void QComboBoxEx::setCompleter(QAbstractItemModel* model) {
    auto completer = new QCompleter(model, this);
    setCompleter(completer);
}
