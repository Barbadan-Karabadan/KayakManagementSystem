#include "financewindow.h"
#include "ui_financewindow.h"

FinanceWindow::FinanceWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FinanceWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Kontakte Verwaltung");

    QObject::connect(ui->newButton, SIGNAL(clicked()), SLOT(neuerKontakt()));
    // QObject::connect(ui->plzButton, SIGNAL(clicked()), SLOT(plzVerwaltung()));
    QObject::connect(ui->searchButton, SIGNAL(clicked()), SLOT(suchen()));
    QObject::connect(ui->actionNeuer_Kontakt, SIGNAL(triggered()), SLOT(neuerKontakt()));
    QObject::connect(ui->actionVerwaltung_Postleitzahlen, SIGNAL(triggered()), SLOT(plzVerwaltung()));
    QObject::connect(ui->actionVerlassen, SIGNAL(triggered()), SLOT(verlassen()));
    QObject::connect(ui->dbView, SIGNAL(clicked(QModelIndex)), SLOT(editKontakt(QModelIndex)));

    sql = new QSqlQueryModel();
    // DB-Anzeigen
    sqlquery(false);
}

FinanceWindow::~FinanceWindow()
{
    delete ui;
    delete sql;
}

void FinanceWindow::neuerKontakt()
{
    FinanceDialog perwindow;
    // Modales Window:
    // Es ist das oberste Window
    // alle anderen Windows sind nicht bedienbar
    perwindow.setModal(true);
    perwindow.show();
    perwindow.exec();

    // hier wurde das Window wieder geschlossen
    // Update der FinanceDialogenliste
    sqlquery(false);
}

void FinanceWindow::editKontakt(QModelIndex index)
{
    // Zeile in der Tableview, auf die geklickt wurde
    int row = index.row();
    // wir holen mit der Zeile die versteckte PId heraus
    int pid = ui->dbView->model()->index(row, 0).data().toInt();

    // FinanceDialogen - Window starten
    FinanceDialog perwindow(this, pid);
    // Modales Window:
    // Es ist das oberste Window
    // alle anderen Windows sind nicht bedienbar
    perwindow.setModal(true);
    perwindow.show();
    perwindow.exec();

    // hier wurde das Window wieder geschlossen
    // Update der FinanceDialogenliste
    sqlquery(false);
}

void FinanceWindow::plzVerwaltung()
{

}

void FinanceWindow::suchen()
{
    sqlquery(true);
}

void FinanceWindow::verlassen()
{
    this->close();
}

void FinanceWindow::sqlquery(bool filter)
{
    QString query = "select id,totalincome,totalexpense,totalbalance from finance";
    if (filter)
    {
        QString name = ui->searchTextEdit->text();
        if (!name.isEmpty())
            query += " where PName like '" + name + "%'";
    }
    sql->setQuery(query);
    sql->setHeaderData(0, Qt::Horizontal, "id");
    sql->setHeaderData(1, Qt::Horizontal, "totalincome");
    sql->setHeaderData(2, Qt::Horizontal, "totalexpense");
    sql->setHeaderData(3, Qt::Horizontal, "totalbalance");

    // Verbinden des Models mit der View
    ui->dbView->setModel(sql);
    // Id unterdrücken
    ui->dbView->hideColumn(0);
}
