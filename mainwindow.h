#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "chatgui.h"
#include "chatslist.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();
    void setCurrentChatGUIObj(QString chatId);
protected:
    ChatsList* chatsList;

private:
    ChatGUI* currentChatGUIObj = nullptr;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
