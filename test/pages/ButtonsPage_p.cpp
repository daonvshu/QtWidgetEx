#include "ButtonsPage.h"
#include "ButtonsPage_p.h"

#include "ui_Buttons.h"

#include <qmessagebox.h>
#include <qdebug.h>

#include <qmenu.h>
#include <qaction.h>

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

		buttonex_icon_settype->items << "pixmap" << "image" << "image path" << "icon" << "network";
	}
};

void ButtonsPagePrivate::bindView(QWidget* parent) {
	view = new ButtonsPageView;
	view->initUi(parent);

	view->buttonex_click3->clickEvt.add(this, &ButtonsPagePrivate::showBtnClickInMemberFunction);

	view->buttonex_press3->pressEvt.add(this, &ButtonsPagePrivate::showBtnPressInMemberFunction);

	view->buttonex_change_text->pressEvt.add(this, &ButtonsPagePrivate::setButtonExTextTest);

	view->buttonex_change_icon->pressEvt.add(this, &ButtonsPagePrivate::setButtonExIconTest);

	view->buttonex_g1->group.create(view->buttonex_g2, view->buttonex_g3);
	view->buttonex_exclusive->stateEvt += [&](int state) {
	    if (state == Qt::Checked) {
			view->buttonex_g1->group.exclusive = true;
	    } else if (state == Qt::Unchecked) {
			view->buttonex_g1->group.exclusive = false;
	    }
	};

	view->buttonex_g1->group.id = 2;
	view->buttonex_g2->group.id = 3;
	view->buttonex_g3->group.id = 4;

	view->buttonex_g1->group += [&] (bool checked) {
		if (checked) {
			QMessageBox::warning(0, "title", "button 1 clicked!");
		}
	};

	view->buttonex_g2->group += [&](int id, bool checked) {
		if (checked) {
			QMessageBox::warning(0, "title", "button 2 clicked! id = " + QString::number(id));
		}
	};


	view->checkboxex1->group.create(view->checkboxex2, view->checkboxex3);
	view->checkboxex_exclusive->stateEvt += [&](int state) {
		if (state == Qt::Checked) {
			view->checkboxex1->group.exclusive = true;
		} else if (state == Qt::Unchecked) {
			view->checkboxex1->group.exclusive = false;
		}
	};

	view->checkboxex_change_text->clickEvt.add(this, &ButtonsPagePrivate::setCheckBoxExTextTest);
	view->checkboxex_change_icon->clickEvt.add(this, &ButtonsPagePrivate::setCheckBoxExIconTest);

	view->checkboxex_get_state->clickEvt += [&](bool) {
		QString stateStr;
		Qt::CheckState state = view->checkboxex_target->state();
		QDebug(&stateStr) << state;
		QMessageBox::warning(0, "title", "checkbox state:" + stateStr);
	};

	view->radioex1->group.create(view->radioex2, view->radioex3);
	view->radiobuttonex_exclusive->stateEvt += [&](int state) {
		if (state == Qt::Checked) {
			view->radioex1->group.exclusive = true;
		} else if (state == Qt::Unchecked) {
			view->radioex1->group.exclusive = false;
		}
	};

	view->toolbtnex1->group.create(view->toolbtnex2, view->toolbtnex3);
	view->toolbuttonex_exclusive->stateEvt += [&](int state) {
		if (state == Qt::Checked) {
			view->toolbtnex1->group.exclusive = true;
		} else if (state == Qt::Unchecked) {
			view->toolbtnex1->group.exclusive = false;
		}
	};

	view->toolbtnex1->group += [&](bool checked) {
		view->toolbtnex1->icon = checked ? ":/WidgetExTest/res/1.png" : "";
	};

	view->toolbtnex2->group += [&](bool checked) {
		view->toolbtnex2->icon = checked ? ":/WidgetExTest/res/1.png" : "";
	};

	auto menu = new QMenu(view->toolbtnex4);
	menu->addAction("action1");
	menu->addAction("action2");

	view->toolbtnex4->setMenu(menu);
	view->toolbtnex4->triggerEvt += [](QAction* action) {
		QMessageBox::warning(0, "title", "trigger action -> " + action->text());
	};
}

ButtonsPagePrivate::~ButtonsPagePrivate() {
	delete view;
}

bool ButtonsPagePrivate::setInThread() {
	return view->set_in_work_thread->checked();
}

int ButtonsPagePrivate::getButtonExIconType() {
	return view->buttonex_icon_settype->curIndex();
}

void ButtonsPagePrivate::showBtnClickInMemberFunction() {
	QMessageBox::warning(0, "title", "button click in member function!");
}

void ButtonsPagePrivate::showBtnPressInMemberFunction() {
	QMessageBox::warning(0, "title", "button press in member function!");
}

void ButtonsPagePrivate::setButtonExText(const QString& text) {
	view->buttonex_change_text->text = text;
}

void ButtonsPagePrivate::setButtonExIcon(const QPixmap& pixmap) {
	view->buttonex_change_icon->icon.targetW(18) = pixmap;
}

void ButtonsPagePrivate::setButtonExIcon(const QImage& image) {
	view->buttonex_change_icon->icon.targetH(20) = image;
}

void ButtonsPagePrivate::setButtonExIcon(const QString& imagePath) {
	view->buttonex_change_icon->icon.target(22, 22) = imagePath;
}

void ButtonsPagePrivate::setButtonExIcon(const QIcon& icon) {
	view->buttonex_change_icon->icon.targetW(24) = icon;
}

void ButtonsPagePrivate::setButtonExIconNet(const QString& url) {
	view->buttonex_change_icon->icon.targetW(26).network(url);
}

void ButtonsPagePrivate::setCheckBoxExText(const QString& text) {
	view->checkboxex_target->text = text;
}

void ButtonsPagePrivate::setCheckBoxExIcon(const QString& filepath) {
	view->checkboxex_target->icon.target(22, 22) = filepath;
}
