#ifndef FINANCEWINDOW_H
#define FINANCEWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include "financedialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class FinanceWindow; }
QT_END_NAMESPACE

class FinanceWindow : public QMainWindow
{
    Q_OBJECT

public:
    FinanceWindow(QWidget *parent = nullptr);
    ~FinanceWindow();

public slots:
    void neuerKontakt();
    void editKontakt(QModelIndex);
    void plzVerwaltung();
    void suchen();
    void verlassen();

private:
    Ui::FinanceWindow *ui;
    QSqlQueryModel *sql;
    void sqlquery(bool filter);
};
#endif // FINANCEWINDOW_H
