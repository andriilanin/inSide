#ifndef DELETECHATCONFIRM_H
#define DELETECHATCONFIRM_H

#include <QDialog>
#include <chatdatabase.h>

namespace Ui {
class deleteChatConfirm;
}

class deleteChatConfirm : public QDialog
{
    Q_OBJECT

public:
    explicit deleteChatConfirm(QWidget *parent = nullptr, const QString chatId = "");
    ~deleteChatConfirm();


signals:
    void confirmSignal();

protected:
    void confirm();
    void cancel();

private:
    QString chatId;
    ChatDatabase* DB;
    Ui::deleteChatConfirm *ui;
};

#endif // DELETECHATCONFIRM_H
