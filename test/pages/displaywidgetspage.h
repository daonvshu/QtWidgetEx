#pragma once

#include "../lifecycle/lifecycle/LifeCycleWidget.h"

const char name_DisplayWidgetsPage[] = "DisplayWidgetsPage";
struct DisplayWidgetsPagePrivate;
class DisplayWidgetsPage : public LifeCycleWidget<Mode_Standard, name_DisplayWidgetsPage> {
	Q_DECLARE_PRIVATE(DisplayWidgetsPage);

public:
	DisplayWidgetsPage(QWidget* parent);
	~DisplayWidgetsPage();

	bool attempClose();

protected:
	void onNavigateResult(const QVariant& data);
	void onViewLoad();
	void onReshow();
	void onHidden();
	void onResizeWindow();
};
