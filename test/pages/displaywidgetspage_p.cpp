#include "displaywidgetspage.h"
#include "displaywidgetspage_p.h"

#include "ui_DisplayWidgets.h"

#include "../asyncsettertest.h"

#include <qmessagebox.h>

QString TextTestDataConverter(const QVariant& data) {
	auto textData = data.value<TextTestData>();
	return textData.data;
}

void showPressInFunctionCallback() {
	QMessageBox::warning(0, "title", "press in function!");
}

struct DisplayWidgetsPageView : public BaseView<Ui::DisplayWidgets> {

	void initUi(QWidget* parent) override {
		setupUi(parent);

		labelex_img_set_type->addItems(QStringList() << "QPixmap" << "QImage" << "QBitmap" << "image path" << "from network");
		labelex_img_set_type->setCurrentIndex(0);

		labelex_img_set_clear->pressEvt += [&] {
			set_image_test_label->clear();
		};

		labelex_gif_speed->addItems(QStringList() << "100" << "200" << "300");

		press_in_lambda->press += [&] {
			QMessageBox::warning(0, "title", "press in lambda!");
		};

		press_in_function->press += showPressInFunctionCallback;

		press_in_member_function->press.add(this, &DisplayWidgetsPageView::showPressInMemberFunctionCallback);

		async_setter_test->clickEvt += [=](bool) {
			(new AsyncSetterTest(parent))->start();
		};
	}

	void showPressInMemberFunctionCallback() {
		QMessageBox::warning(0, "title", "press in member function!");
	}
};

void DisplayWidgetsPagePrivate::bindView(QWidget* parent) {
	view = new DisplayWidgetsPageView;
	view->initUi(parent);

	view->labelex_text_set->clickEvt.add(this, &DisplayWidgetsPagePrivate::setLabelExTextTest);
	view->labelex_text_set_use_converter->clickEvt.add(this, &DisplayWidgetsPagePrivate::setLabelExTextTestByConverter);

	view->labelex_img_set->clickEvt.add(this, &DisplayWidgetsPagePrivate::setLabelExImgTest);

	view->labelex_gif_set->clickEvt.add(this, &DisplayWidgetsPagePrivate::setLabelExGifTest);
	view->labelex_gif_start->clickEvt += [&] (bool) { view->set_gif_test_label->gif()->start(); };
	view->labelex_gif_stop->clickEvt += [&](bool) {view->set_gif_test_label->gif()->stop(); };
	view->labelex_gif_pause->clickEvt += [&](bool) {
		view->set_gif_test_label->gif()->setPaused(view->set_gif_test_label->gif()->state() != QMovie::Paused);
	};

	connect(view->labelex_gif_speed, qOverload<const QString&>(&QComboBox::currentIndexChanged), [&](const QString& str) {
		auto m = view->set_gif_test_label->gif();
		if (m != nullptr) {
			m->setSpeed(str.toInt());
		}
	});
}

bool DisplayWidgetsPagePrivate::setInThread() {
	return view->set_in_work_thread->isChecked();;
}

void DisplayWidgetsPagePrivate::useConverter(bool use) {
	view->set_text_test_label->text.dataConvert = use ? TextTestDataConverter : nullptr;
}

int DisplayWidgetsPagePrivate::getImgSetType() {
	return view->labelex_img_set_type->currentIndex();
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

void DisplayWidgetsPagePrivate::setLabelExImg(const QPixmap& pixmap) {
	view->set_image_test_label->image.target(350, 400, Qt::IgnoreAspectRatio) = pixmap;
}

void DisplayWidgetsPagePrivate::setLabelExImg(const QImage& image) {
	view->set_image_test_label->image.targetW(300) = image;
}

void DisplayWidgetsPagePrivate::setLabelExImg(const QBitmap& bitmap) {
	view->set_image_test_label->image.target(250, 250) = bitmap;
}

void DisplayWidgetsPagePrivate::setLabelExImg(const QString& imagePath) {
	view->set_image_test_label->image.target(200, 200) = imagePath;
}

void DisplayWidgetsPagePrivate::setLabelExImg(const QString& urlImg, const QSize& tagSize) {
	view->set_image_test_label->image.target(tagSize).network(urlImg);
}


void DisplayWidgetsPagePrivate::setLabelExGif(const QString& path) {
	view->labelex_gif_speed->setCurrentIndex(0);
	view->set_gif_test_label->gif = path;
}
