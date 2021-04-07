#include "InputWidgetsPage.h"
#include "InputWidgetsPage_p.h"

#include "../utils/RunnableHandler.h"

InputWidgetsPage::InputWidgetsPage(QWidget* parent)
	: LifeCycleWidget(*new InputWidgetsPagePrivate, parent)
{
	Q_D(InputWidgetsPage);
	d->init();
}

InputWidgetsPage::~InputWidgetsPage() {
}

bool InputWidgetsPage::attempClose() {
	return true;
}

void InputWidgetsPage::onNavigateResult(const QVariant& data) {}

void InputWidgetsPage::onViewLoad() {}

void InputWidgetsPage::onReshow() {}

void InputWidgetsPage::onHidden() {}

void InputWidgetsPage::onResizeWindow() {}

void InputWidgetsPagePrivate::init() {
	Q_Q(InputWidgetsPage);
	bindView(q);
}

void InputWidgetsPagePrivate::setLineEditExReadOnlyTest() {
    if (setInThread()) {
		RunnableHandler<void>::exec([&] {
			setLineEditExReadOnly();
		});
    } else {
		setLineEditExReadOnly();
    }
}
