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

		comboboxex->curIndexChangeEvt += [&](int index) {
			comboex_current_index1->text = index;
		};

		comboboxex->curTextChangeEvt += [&](const QString& text) {
			comboex_current_text1->text = text;
		};

		comboex_get_current_value->clickEvt += [&](bool) {
			comboex_current_index2->text = comboboxex->curIndex();
			comboex_current_text2->text = comboboxex->curText();
		};

		comboex_get_current_size->clickEvt += [&](bool) {
			comboex_current_size->text = comboboxex->items.size();
		};

		comboex_item_completer->clickEvt += [&](bool) {
			comboboxex->setCompleter();
		};

		comboex_words_completer->clickEvt += [&](bool) {
			QStringList words;
			words << "push button" << "check box" << "label" << "line edit" << "combobox" << "widget";
			comboboxex->setCompleter(words);
		};
	}
};

void InputWidgetsPagePrivate::bindView(QWidget* parent) {
	view = new InputWidgetsPageView;
	view->initUi(parent);

	view->read_only_set->clickEvt.add(this, &InputWidgetsPagePrivate::setLineEditExReadOnlyTest);

	view->comboex_add_items->clickEvt.add(this, &InputWidgetsPagePrivate::addItemToComboBoxExTest);

	view->comboex_modify->clickEvt.add(this, &InputWidgetsPagePrivate::modifyComboBoxExCurrentItemTest);

	view->comboex_insert->clickEvt.add(this, &InputWidgetsPagePrivate::insertToComboBoxExTest);

	view->comboex_remove->clickEvt.add(this, &InputWidgetsPagePrivate::removeCurrentFromComboBoxExTest);
}

InputWidgetsPagePrivate::~InputWidgetsPagePrivate() {
	delete view;
}

bool InputWidgetsPagePrivate::setInThread() {
	return view->set_in_work_thread->isChecked();
}

void InputWidgetsPagePrivate::setLineEditExReadOnly() {
	view->read_only_test_input->readOnly = !view->read_only_test_input->readOnly();
}

void InputWidgetsPagePrivate::addItemToComboBoxExTest() {
	static int i = 0;
	auto tail = QString::number(i++);
	view->comboboxex->clear();
	view->comboboxex->items << "c++ " + tail << "java " + tail << "javascript " + tail << "c# " + tail
		<< "python " + tail << "php " + tail << "html " + tail << "qss " + tail;
	view->comboboxex->curIndex = 0;
}

void InputWidgetsPagePrivate::modifyComboBoxExCurrentItemTest() {
	int index = view->comboboxex->curIndex();
	QString text = view->comboboxex->curText();
	view->comboboxex->items(index).text = text + "_m" + QString::number(index);
}

void InputWidgetsPagePrivate::insertToComboBoxExTest() {
	static int i = 0;
	auto text = QString("insert item %1").arg(i++);
	int index = view->comboboxex->curIndex();
	view->comboboxex->items.insert(index, text);
}

void InputWidgetsPagePrivate::removeCurrentFromComboBoxExTest() {
	int index = view->comboboxex->curIndex();
	view->comboboxex->items.remove(index);
}
