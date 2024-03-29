#include "displaywidgetspage.h"
#include "displaywidgetspage_p.h"

#include "../utils/runnablehandler.h"

#include <qbitmap.h>
#include <qbuffer.h>
#include <qtimer.h>

DisplayWidgetsPage::DisplayWidgetsPage(QWidget* parent)
	: LifeCycleWidget(*new DisplayWidgetsPagePrivate, parent)
{
	Q_D(DisplayWidgetsPage);
	d->init();
}

DisplayWidgetsPage::~DisplayWidgetsPage() {
}

bool DisplayWidgetsPage::attempClose() {
	return true;
}

void DisplayWidgetsPage::onNavigateResult(const QVariant& data) {}

void DisplayWidgetsPage::onViewLoad() {}

void DisplayWidgetsPage::onReshow() {}

void DisplayWidgetsPage::onHidden() {}

void DisplayWidgetsPage::onResizeWindow() {}

void DisplayWidgetsPagePrivate::init() {
	Q_Q(DisplayWidgetsPage);
	bindView(q);
}

void DisplayWidgetsPagePrivate::setLabelExTextTest() {
	useConverter(false);
    if (setInThread()) {
		RunnableHandler<void>::exec([&] {
			setLabelExText("set text in work thread!");
		});
    } else {
		setLabelExText("set text finished!");
    }
}

void DisplayWidgetsPagePrivate::setLabelExTextTestByConverter() {
	useConverter(true);
	if (setInThread()) {
		RunnableHandler<void>::exec([&] {
			setLabelExTextByConverter({ 0, "set data in work thread!" });
		});
	} else {
		setLabelExTextByConverter({ 1, "set data finished!" });
	}
}

void DisplayWidgetsPagePrivate::setLabelExImgTest() {
	auto setter = [&] {
		QImage image(":/WidgetExTest/res/1.png");
        switch (getImgSetType()) {
		case 0:
			setLabelExImg(QPixmap::fromImage(image));
			break;
		case 1:
			setLabelExImg(image);
			break;
		case 2:
			setLabelExImg(QBitmap::fromImage(image));
			break;
		case 3:
			setLabelExImg(":/WidgetExTest/res/1.png");
			break;
		case 4:
			setLabelExImg("https://avatars.githubusercontent.com/u/30491545?v=4", QSize(200, 200));
			break;
        }
	};
	if (setInThread()) {
		RunnableHandler<void>::exec(setter);
	} else {
		setter();
	}
}

void DisplayWidgetsPagePrivate::setLabelExGifTest() {
	if (setInThread()) {
		RunnableHandler<void>::exec([&] {
			setLabelExGif(":/WidgetExTest/res/2.gif");
		});
	} else {
		setLabelExGif(":/WidgetExTest/res/2.gif");
	}
}

void DisplayWidgetsPagePrivate::setProgressTest() {
	static int num;
	num = 0;
	if (setInThread()) {
		RunnableHandler<void>::exec([&] {
            while (num++ < 100) {
				setProgressBarValue(num);
				QThread::msleep(50);
            }
		});
	} else {
		auto timer = new QTimer(this);
		connect(timer, &QTimer::timeout, this, [&, timer] {
			if (num++ >= 100) {
				timer->stop();
			}
			setProgressBarValue(num);
		});
		timer->start(50);
	}
}
