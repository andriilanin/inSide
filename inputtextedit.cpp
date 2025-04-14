#include "InputTextEdit.h"

InputTextEdit::InputTextEdit(QWidget* parent)
    : QTextEdit(parent)
{
    this->setStyleSheet("background: rgb(24,36,44);\n");
}

void InputTextEdit::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        if (event->modifiers() & Qt::ShiftModifier) {
            QTextEdit::keyPressEvent(event);
        } else {
            emit enterPressed();
        }
    } else {
        QTextEdit::keyPressEvent(event);
    }
}
