#include "utils/buttongrouputil.h"

#include <qbuttongroup.h>

EX_BEGIN_NAMESPACE
class IdSetterCallback : public SimpleDataTargetSetterCallback<int, ButtonGroupUtil> {
public:
    using SimpleDataTargetSetterCallback::SimpleDataTargetSetterCallback;

    void setData(const int& id) override {
        auto group = target->button->group();
        Q_ASSERT_X(group != nullptr, "set id", "button group not set!");
        group->setId(target->button, id);
    }

    int getData() override {
        auto group = target->button->group();
        Q_ASSERT_X(group != nullptr, "get id", "button group not set!");
        return group->id(target->button);
    }
};

class ExclusiveCallback : public SimpleDataTargetSetterCallback<bool, ButtonGroupUtil> {
public:
    using SimpleDataTargetSetterCallback::SimpleDataTargetSetterCallback;

    void setData(const bool& exclusive) override {
        auto group = target->button->group();
        Q_ASSERT_X(group != nullptr, "set exclusive", "button group not set!");
        group->setExclusive(exclusive);
    }

    bool getData() override {
        auto group = target->button->group();
        Q_ASSERT_X(group != nullptr, "get exclusive", "button group not set!");
        return group->exclusive();
    }
};
EX_END_NAMESPACE

ButtonGroupUtil::ButtonGroupUtil(QAbstractButton* button)
    : QObject(button)
    , button(button)
    , id(new _widget_ex::IdSetterCallback(this))
    , exclusive(new _widget_ex::ExclusiveCallback(this))
{
}

void ButtonGroupUtil::operator+=(const std::function<void(bool)>& clickCallback) {
    auto group = button->group();
    Q_ASSERT_X(group != nullptr, "click event", "button group not set!");
    QObject::connect(group, qOverload<QAbstractButton*>(&QButtonGroup::buttonClicked), [=](QAbstractButton* btn) {
        clickCallback(btn == this->button);
    });
}

#if (QT_VERSION >= QT_VERSION_CHECK(5, 15, 0))
void ButtonGroupUtil::operator+=(const std::function<void(int, bool)>& idClickCallback) {
    auto group = button->group();
    Q_ASSERT_X(group != nullptr, "click event", "button group not set!");
    QObject::connect(group, &QButtonGroup::idClicked, [=](int id) {
        idClickCallback(id, group->id(this->button) == id);
    });
}
#endif

QButtonGroup* ButtonGroupUtil::operator()() {
    return button->group();
}

void ButtonGroupUtil::create(int size, ...) {
    va_list valist;

    auto group = button->group();
    if (group == nullptr) {
        group = new QButtonGroup(button);
        group->addButton(button);
    }

    va_start(valist, size);

    for (int i=0; i<size; i++) {
        auto btn = va_arg(valist, QAbstractButton*);
        Q_ASSERT_X(btn->group() == nullptr, "create group", "target buttons already contains a group");
        group->addButton(btn);
    }

    va_end(valist);
}
