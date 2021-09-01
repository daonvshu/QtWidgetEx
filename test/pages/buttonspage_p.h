#pragma once

#include "../lifecycle/lifecycle/Impl.h"

struct ButtonsPageView;
struct ButtonsPagePrivate : public ImplPrivate {
	Q_DECLARE_PUBLIC(ButtonsPage);

	void init();
	void bindView(QWidget* parent);
	bool setInThread();

	int getButtonExIconType();

	void showBtnClickInMemberFunction();
	void showBtnPressInMemberFunction();

	void setButtonExText(const QString& text);

	void setButtonExIcon(const QPixmap& pixmap);
	void setButtonExIcon(const QImage& image);
	void setButtonExIcon(const QString& imagePath);
	void setButtonExIcon(const QIcon& icon);
	void setButtonExIconNet(const QString& url);

	void setCheckBoxExText(const QString& text);

	void setCheckBoxExIcon(const QString& filepath);


	void setButtonExTextTest();

	void setButtonExIconTest();

	void setCheckBoxExTextTest();

	void setCheckBoxExIconTest();

	ButtonsPageView* view;

	~ButtonsPagePrivate();
};
