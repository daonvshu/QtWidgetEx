#include "ButtonsPage.h"
#include "ButtonsPage_p.h"

#include "../utils/RunnableHandler.h"

#include <qicon.h>

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

void ButtonsPagePrivate::setButtonExTextTest() {
	static int changeCount = 0;
    if (setInThread()) {
        RunnableHandler<void>::exec([&] {
			setButtonExText("change in thr count:" + QString::number(changeCount++));
        });
    } else {
		setButtonExText("change count:" + QString::number(changeCount++));
    }
}

void ButtonsPagePrivate::setButtonExIconTest() {
	auto setter = [&] {
		QImage image(":/WidgetExTest/res/1.png");
		switch (getButtonExIconType()) {
		case 0:
			setButtonExIcon(QPixmap::fromImage(image));
			break;
		case 1:
			setButtonExIcon(image);
			break;
		case 2:
			setButtonExIcon(":/WidgetExTest/res/1.png");
			break;
		case 3:
			setButtonExIcon(QIcon(":/WidgetExTest/res/1.png"));
			break;
		case 4:
			setButtonExIconNet("https://avatars.githubusercontent.com/u/30491545?v=4");
			break;
		}
	};
	if (setInThread()) {
		RunnableHandler<void>::exec(setter);
	} else {
		setter();
	}
}

void ButtonsPagePrivate::setCheckBoxExTextTest() {
    if (setInThread()) {
		RunnableHandler<void>::exec([&] {
			setCheckBoxExText("change text in thread");
		});
    } else {
		setCheckBoxExText("change text");
    }
}

void ButtonsPagePrivate::setCheckBoxExIconTest() {
    if (setInThread()) {
		RunnableHandler<void>::exec([&] {
			setCheckBoxExIcon(":/WidgetExTest/res/1.png");
		});
    } else {
		setCheckBoxExIcon(":/WidgetExTest/res/1.png");
    }
}
