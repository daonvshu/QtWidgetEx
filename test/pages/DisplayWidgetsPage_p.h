﻿#pragma once

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
	void setLabelExImg(const QString& base64);

	void setLabelExGif(const QString& path);
	//view model

	void setLabelExTextTest();
	void setLabelExTextTestByConverter();

	void setLabelExImgTest();

	void setLabelExGifTest();

	DisplayWidgetsPageView* view;

	~DisplayWidgetsPagePrivate();
};
