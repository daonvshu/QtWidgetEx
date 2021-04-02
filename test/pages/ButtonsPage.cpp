#include "ButtonsPage.h"
#include "ButtonsPage_p.h"

ButtonsPage::ButtonsPage(QWidget* parent)
	: LifeCycleWidget(*new ButtonsPagePrivate, parent)
{
	Q_D(ButtonsPage);
	d->init();
}

ButtonsPage::~ButtonsPage() {
}

bool ButtonsPage::attempClose() {
	return true;
}

void ButtonsPage::onNavigateResult(const QVariant& data) {}

void ButtonsPage::onViewLoad() {}

void ButtonsPage::onReshow() {}

void ButtonsPage::onHidden() {}

void ButtonsPage::onResizeWindow() {}

void ButtonsPagePrivate::init() {
	Q_Q(ButtonsPage);
	bindView(q);
}
