#pragma once

#include "LiveData.h"
#include "LiveDataDefaultConverter.h"

#include <qtextedit.h>

static QTextEdit* castTextEditWithCheck(QWidget* widget) {
    auto textEdit = dynamic_cast<QTextEdit*>(widget);
    Q_ASSERT_X(textEdit != nullptr, "textEditnotify", "cannot cast widget");
    return textEdit;
}

template<typename T>
static void textEdit_textChanged(QWidget* widget, LiveData<T>* liveData) {
    auto editor = castTextEditWithCheck(widget);
    QObject::connect(editor, &QTextEdit::textChanged, [=]() {
        liveData->setData(editor->toPlainText());
    });
}