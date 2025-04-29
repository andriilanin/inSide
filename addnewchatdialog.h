#ifndef ADDNEWCHATDIALOG_H
#define ADDNEWCHATDIALOG_H

#include <QDialog>
#include <QHBoxLayout>
#include "chatdatabase.h"
#include <vector>
namespace Ui {
class AddNewChatDialog;
}

class AddNewChatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewChatDialog(QWidget *parent = nullptr);
    ~AddNewChatDialog();

private slots:
    void addNewChatButtonPressed();

protected:
    void addNewUserArea();
    void deleteNewUserArea();

private:
    std::vector<QHBoxLayout*> usersLayouts;
    ChatDatabase* DB;
    Ui::AddNewChatDialog *ui;
};

#endif // ADDNEWCHATDIALOG_H
