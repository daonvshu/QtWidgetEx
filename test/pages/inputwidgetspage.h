#pragma once

#include "../lifecycle/lifecycle/LifeCycleWidget.h"

const char name_InputWidgetsPage[] = "InputWidgetsPage";
struct InputWidgetsPagePrivate;
class InputWidgetsPage : public LifeCycleWidget<Mode_Standard, name_InputWidgetsPage> {
	Q_DECLARE_PRIVATE(InputWidgetsPage);

public:
	InputWidgetsPage(QWidget* parent);
	~InputWidgetsPage();

	bool attempClose();

protected:
	void onNavigateResult(const QVariant& data);
	void onViewLoad();
	void onReshow();
	void onHidden();
	void onResizeWindow();
};
