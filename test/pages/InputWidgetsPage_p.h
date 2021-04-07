#pragma once

#include "../lifecycle/lifecycle/Impl.h"

struct InputWidgetsPageView;
struct InputWidgetsPagePrivate : public ImplPrivate {
	Q_DECLARE_PUBLIC(InputWidgetsPage);

	void init();
	void bindView(QWidget* parent);

	bool setInThread();

	void setLineEditExReadOnly();

	void setLineEditExReadOnlyTest();

	InputWidgetsPageView* view;

	~InputWidgetsPagePrivate();
};
