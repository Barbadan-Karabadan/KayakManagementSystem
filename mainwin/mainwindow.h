#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

#include "member/memberwindow.h"
#include "member/memberdialog.h"

#include "mitglied/mitgliedwindow.h"
#include "mitglied/mitglieddialog.h"

#include "boat/boatwindow.h"
#include "boat/boatdialog.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
class QMdiArea;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


public slots:
    void newMember();
    void listMembers();
    void newMitglied();
    void listMitglied();
    void addBoat();
    void updateActions();

private:
    Ui::MainWindow *ui;

    void createMenus();
    void createActions();

    QMdiArea *mdiArea;
};
#endif // MAINWINDOW_H
