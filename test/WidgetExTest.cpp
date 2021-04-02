#include "WidgetExTest.h"

#include "lifecycle/lifecycle/FragmentManager.h"

#include "pages/DisplayWidgetsPage.h"

#include <qstandarditemmodel.h>

WidgetExTest::WidgetExTest(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    auto fragmentManager = new FragmentManager(ui.stackedWidget);
    fragmentManager->registerPage<
        DisplayWidgetsPage
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
    model->appendRow(item);

    item = new QStandardItem("Input Widgets"); 
    model->appendRow(item);
}
