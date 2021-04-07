#include "InputWidgetsPage.h"
#include "InputWidgetsPage_p.h"

#include "ui_InputWidgets.h"

struct InputWidgetsPageView : public BaseView<Ui::InputWidgets> {

	void initUi(QWidget* parent) override {
		setupUi(parent);
		//do other view init..
		lineeditex_edit_finish_test->editFinishEvt += [&] {
			lineeditex_event_test->text = lineeditex_edit_finish_test->text();
		};

		lineeditex_return_press_test->returnPressEvt += [&] {
			lineeditex_event_test->text = lineeditex_return_press_test->text();
		};

		lineeditex_text_change_test->textChangeEvt += [&](const QString& text) {
			lineeditex_event_test->text = text;
		};

		lineeditex_text_edit_test->textEditEvt += [&](const QString& text) {
			lineeditex_event_test->text = text;
		};
	}
};

void InputWidgetsPagePrivate::bindView(QWidget* parent) {
	view = new InputWidgetsPageView;
	view->initUi(parent);

	view->read_only_set->clickEvt.add(this, &InputWidgetsPagePrivate::setLineEditExReadOnlyTest);
}

InputWidgetsPagePrivate::~InputWidgetsPagePrivate() {
	delete view;
}

bool InputWidgetsPagePrivate::setInThread() {
	return view->set_in_work_thread->isChecked();;
}

void InputWidgetsPagePrivate::setLineEditExReadOnly() {
	view->read_only_test_input->readOnly = !view->read_only_test_input->readOnly();
}
