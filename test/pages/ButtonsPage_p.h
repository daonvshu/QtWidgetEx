#pragma once

#include "../lifecycle/lifecycle/Impl.h"

struct ButtonsPageView;
struct ButtonsPagePrivate : public ImplPrivate {
	Q_DECLARE_PUBLIC(ButtonsPage);

	void init();
	void bindView(QWidget* parent);

	void showBtnClickInMemberFunction();
	void showBtnPressInMemberFunction();

	ButtonsPageView* view;

	~ButtonsPagePrivate();
};
