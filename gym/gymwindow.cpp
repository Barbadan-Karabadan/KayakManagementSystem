#include "gymwindow.h"
#include "ui_gymwindow.h"

GymWindow::GymWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GymWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Trainigs Program");

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

GymWindow::~GymWindow()
{
    delete ui;
    delete sql;
}

void GymWindow::neuerKontakt()
{
    GymDialog perwindow;
    // Modales Window:
    // Es ist das oberste Window
    // alle anderen Windows sind nicht bedienbar
    perwindow.setModal(true);
    perwindow.show();
    perwindow.exec();

    // hier wurde das Window wieder geschlossen
    // Update der GymDialogenliste
    sqlquery(false);
}

void GymWindow::editKontakt(QModelIndex index)
{
    // Zeile in der Tableview, auf die geklickt wurde
    int row = index.row();
    // wir holen mit der Zeile die versteckte PId heraus
    int pid = ui->dbView->model()->index(row, 0).data().toInt();

    // GymDialogen - Window starten
    GymDialog perwindow(this, pid);
    // Modales Window:
    // Es ist das oberste Window
    // alle anderen Windows sind nicht bedienbar
    perwindow.setModal(true);
    perwindow.show();
    perwindow.exec();

    // hier wurde das Window wieder geschlossen
    // Update der GymDialogenliste
    sqlquery(false);
}

void GymWindow::plzVerwaltung()
{

}

void GymWindow::suchen()
{
    sqlquery(true);
}

void GymWindow::verlassen()
{
    this->close();
}

void GymWindow::sqlquery(bool filter)
{
    QString query = "select id, pushups, plank, squat, benchPress,deadlift, pullUp, legPress, tricepPushDown, dumbbellRow, seatedRow from gym";
    if (filter)
    {
        QString name = ui->searchTextEdit->text();
        if (!name.isEmpty())
            query += " where PName like '" + name + "%'";
    }
    sql->setQuery(query);
    sql->setHeaderData(0, Qt::Horizontal, "id");
    sql->setHeaderData(1, Qt::Horizontal, "pushups");
    sql->setHeaderData(2, Qt::Horizontal, "plank");
    sql->setHeaderData(3, Qt::Horizontal, "squat");
    sql->setHeaderData(4, Qt::Horizontal, "benchPress");
    sql->setHeaderData(5, Qt::Horizontal, "deadlift");
    sql->setHeaderData(6, Qt::Horizontal, "pullUp");
    sql->setHeaderData(7, Qt::Horizontal, "legPress");
    sql->setHeaderData(8, Qt::Horizontal, "tricepPushDown");
    sql->setHeaderData(9, Qt::Horizontal, "dumbbellRow");
    sql->setHeaderData(10, Qt::Horizontal, "seatedRow");

    // Verbinden des Models mit der View
    ui->dbView->setModel(sql);
    // Id unterdrücken
    ui->dbView->hideColumn(0);
}
