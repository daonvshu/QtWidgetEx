#include "widgetextest.h"

#include "lifecycle/lifecycle/FragmentManager.h"

#include "pages/displaywidgetspage.h"
#include "pages/buttonspage.h"
#include "pages/inputwidgetspage.h"

#include <qstandarditemmodel.h>

WidgetExTest::WidgetExTest(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    auto fragmentManager = new FragmentManager(ui.stackedWidget);
    fragmentManager->registerPage<
        DisplayWidgetsPage,
        ButtonsPage,
        InputWidgetsPage
    >();
    fragmentManager->navigateTo("DisplayWidgetsPage");

    initWidgetTree();

    connect(ui.listView, &QListView::clicked, [=] (const QModelIndex& index) {
        fragmentManager->replaceTo(index.data(Qt::UserRole + 1).toString());
    });
}

void WidgetExTest::initWidgetTree() {
    auto model = new QStandardItemModel(this);
    ui.listView->setModel(model);

    auto item = new QStandardItem("Display Widgets");
    item->setData("DisplayWidgetsPage", Qt::UserRole + 1);
    model->appendRow(item);

    item = new QStandardItem("Buttons");
    item->setData("ButtonsPage", Qt::UserRole + 1);
    model->appendRow(item);

    item = new QStandardItem("Input Widgets");
    item->setData("InputWidgetsPage", Qt::UserRole + 1);
    model->appendRow(item);
}
