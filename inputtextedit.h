#ifndef INPUTTEXTEDIT_H
#define INPUTTEXTEDIT_H

#include <QTextEdit>
#include <QKeyEvent>

class InputTextEdit : public QTextEdit {
    Q_OBJECT

public:
    explicit InputTextEdit(QWidget* parent = nullptr);
    using QTextEdit::QTextEdit;
signals:
    void enterPressed();

protected:
    void keyPressEvent(QKeyEvent* event) override;

private:
    int charCount = 0;


};


#endif // INPUTTEXTEDIT_H
