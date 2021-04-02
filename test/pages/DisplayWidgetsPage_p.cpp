#include "DisplayWidgetsPage.h"
#include "DisplayWidgetsPage_p.h"

#include "ui_DisplayWidgets.h"

QString TextTestDataConverter(const QVariant& data) {
	auto textData = data.value<TextTestData>();
	return textData.data;
}

struct DisplayWidgetsPageView : public BaseView<Ui::DisplayWidgets> {

	void initUi(QWidget* parent) override {
		setupUi(parent);
		//do other view init..
	}
};

void DisplayWidgetsPagePrivate::bindView(QWidget* parent) {
	view = new DisplayWidgetsPageView;
	view->initUi(parent);

	view->labelex_text_set->clickEvt.add(this, &DisplayWidgetsPagePrivate::setLabelExTextTest);
	view->labelex_text_set_use_converter->clickEvt.add(this, &DisplayWidgetsPagePrivate::setLabelExTextTestByConverter);
}

bool DisplayWidgetsPagePrivate::setInThread() {
	return view->set_in_work_thread->isChecked();;
}

void DisplayWidgetsPagePrivate::useConverter(bool use) {
	view->set_text_test_label->text.dataConvert = use ? TextTestDataConverter : nullptr;
}

DisplayWidgetsPagePrivate::~DisplayWidgetsPagePrivate() {
	delete view;
}

void DisplayWidgetsPagePrivate::setLabelExText(const QString& text) {
	view->set_text_test_label->text = text;
}

void DisplayWidgetsPagePrivate::setLabelExTextByConverter(const TextTestData& textTestData) {
	view->set_text_test_label->text = QVariant::fromValue(textTestData);
}