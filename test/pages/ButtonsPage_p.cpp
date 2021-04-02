#include "ButtonsPage.h"
#include "ButtonsPage_p.h"

#include "ui_Buttons.h"

#include <qmessagebox.h>

void showBtnClickInFunction(bool) {
	QMessageBox::warning(0, "title", "button click in function!");
}

void showBtnPressInFunction() {
	QMessageBox::warning(0, "title", "button press in function!");
}

struct ButtonsPageView : public BaseView<Ui::Buttons> {

	void initUi(QWidget* parent) override {
		setupUi(parent);
		//do other view init..

		buttonex_click1->clickEvt += [&](bool) {
			QMessageBox::warning(0, "title", "button click in lambda!");
		};

		buttonex_click2->clickEvt += showBtnClickInFunction;

		buttonex_press1->pressEvt += [&] {
			QMessageBox::warning(0, "title", "button press in lambda!");
		};

		buttonex_press2->pressEvt += showBtnPressInFunction;
	}
};

void ButtonsPagePrivate::bindView(QWidget* parent) {
	view = new ButtonsPageView;
	view->initUi(parent);

	view->buttonex_click3->clickEvt.add(this, &ButtonsPagePrivate::showBtnClickInMemberFunction);

	view->buttonex_press3->pressEvt.add(this, &ButtonsPagePrivate::showBtnPressInMemberFunction);
}

ButtonsPagePrivate::~ButtonsPagePrivate() {
	delete view;
}

void ButtonsPagePrivate::showBtnClickInMemberFunction() {
	QMessageBox::warning(0, "title", "button click in member function!");
}

void ButtonsPagePrivate::showBtnPressInMemberFunction() {
	QMessageBox::warning(0, "title", "button press in member function!");
}
