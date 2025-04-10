#ifndef ADDNEWCHATDIALOG_H
#define ADDNEWCHATDIALOG_H

#include <QDialog>
#include "chatdatabase.h"

namespace Ui {
class addNewChatDialog;
}

class addNewChatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addNewChatDialog(QWidget *parent = nullptr);
    ~addNewChatDialog();


private slots:
    void addNewChatButtonPressed();

private:
    ChatDatabase* DB;
    Ui::addNewChatDialog *ui;
};

#endif // ADDNEWCHATDIALOG_H
