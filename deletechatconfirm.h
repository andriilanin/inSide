#ifndef DELETECHATCONFIRM_H
#define DELETECHATCONFIRM_H

#include <QDialog>
#include <chatdatabase.h>

namespace Ui {
class DeleteChatConfirm;
}

class DeleteChatConfirm : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteChatConfirm(QWidget *parent = nullptr, const QString chatId = "");
    ~DeleteChatConfirm();


signals:
    void confirmSignal();

protected:
    void confirm();
    void cancel();

private:
    QString chatId;
    ChatDatabase* DB;
    Ui::DeleteChatConfirm *ui;
};

#endif // DELETECHATCONFIRM_H
