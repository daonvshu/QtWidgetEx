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

	//view

	void init();
	void bindView(QWidget* parent);
	bool setInThread();
	void useConverter(bool use);
	int getImgSetType();

	void setLabelExText(const QString& text);
	void setLabelExTextByConverter(const TextTestData& textTestData);

	void setLabelExImg(const QPixmap& pixmap);
	void setLabelExImg(const QImage& image);
	void setLabelExImg(const QBitmap& bitmap);
	void setLabelExImg(const QString& imagePath);
	void setLabelExImg(const QString& urlImg, const QSize& tagSize);

	void setLabelExGif(const QString& path);

	void setProgressBarValue(int value);
	//view model

	void setLabelExTextTest();
	void setLabelExTextTestByConverter();

	void setLabelExImgTest();

	void setLabelExGifTest();

	void setProgressTest();

	DisplayWidgetsPageView* view;

	~DisplayWidgetsPagePrivate();
};
