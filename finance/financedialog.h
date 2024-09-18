#ifndef FINANCEDIALOG_H
#define FINANCEDIALOG_H

#include <QDebug>
#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class FinanceDialog;
}

class FinanceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FinanceDialog(QWidget *parent = nullptr, int pid = 0);
    ~FinanceDialog();

public slots:
    void save();
    void loeschen();
    void verlassen();

private:
    Ui::FinanceDialog *ui;
    // Primary Key für die Finance Tabelle
    int pid;
};

#endif // FINANCEDIALOG_H
