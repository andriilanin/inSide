#ifndef ADDNEWCHATDIALOG_H
#define ADDNEWCHATDIALOG_H

#include <QDialog>

namespace Ui {
class addNewChatDialog;
}

class addNewChatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addNewChatDialog(QWidget *parent = nullptr);
    ~addNewChatDialog();

private:
    Ui::addNewChatDialog *ui;
};

#endif // ADDNEWCHATDIALOG_H
