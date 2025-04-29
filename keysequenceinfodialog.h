#ifndef KEYSEQUENCEINFODIALOG_H
#define KEYSEQUENCEINFODIALOG_H

#include <QDialog>
#include <chatdatabase.h>

namespace Ui {
class KeySequenceInfoDialog;
}

class KeySequenceInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit KeySequenceInfoDialog(QWidget *parent = nullptr, const QString chatId = "");
    ~KeySequenceInfoDialog();

private:
    ChatDatabase* DB;
    Ui::KeySequenceInfoDialog *ui;
};

#endif // KEYSEQUENCEINFODIALOG_H
