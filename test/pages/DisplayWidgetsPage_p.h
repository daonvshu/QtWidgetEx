#pragma once

#include "../lifecycle/lifecycle/Impl.h"

struct TextTestData {
	int id;
	QString data;
};
Q_DECLARE_METATYPE(TextTestData);

struct DisplayWidgetsPageView;
struct DisplayWidgetsPagePrivate : public ImplPrivate {
	Q_DECLARE_PUBLIC(DisplayWidgetsPage);

	void init();
	void bindView(QWidget* parent);
	bool setInThread();
	void useConverter(bool use);

	void setLabelExText(const QString& text);
	void setLabelExTextByConverter(const TextTestData& textTestData);

	void setLabelExTextTest();
	void setLabelExTextTestByConverter();

	DisplayWidgetsPageView* view;

	~DisplayWidgetsPagePrivate();
};
