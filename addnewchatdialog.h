#ifndef ADDNEWCHATDIALOG_H
#define ADDNEWCHATDIALOG_H

#include <QDialog>
#include <QHBoxLayout>
#include "chatdatabase.h"
#include <vector>
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

protected:
    void addNewUserArea ();

private:
    std::vector<QHBoxLayout*> UsersLayouts;
    ChatDatabase* DB;
    Ui::addNewChatDialog *ui;
};

#endif // ADDNEWCHATDIALOG_H
