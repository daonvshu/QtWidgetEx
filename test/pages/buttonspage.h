#pragma once

#include "../lifecycle/lifecycle/LifeCycleWidget.h"

const char name_ButtonsPage[] = "ButtonsPage";
class ButtonsPagePrivate;
class ButtonsPage : public LifeCycleWidget<Mode_Standard, name_ButtonsPage> {
	Q_DECLARE_PRIVATE(ButtonsPage);

public:
	ButtonsPage(QWidget* parent);
	~ButtonsPage();

	bool attempClose();

protected:
	void onNavigateResult(const QVariant& data);
	void onViewLoad();
	void onReshow();
	void onHidden();
	void onResizeWindow();
};
