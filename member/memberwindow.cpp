#include "memberwindow.h"
#include "ui_memberwindow.h"

MemberWindow::MemberWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MemberWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Kontakte Verwaltung");

    QObject::connect(ui->newButton, SIGNAL(clicked()), SLOT(neuerKontakt()));
    QObject::connect(ui->plzButton, SIGNAL(clicked()), SLOT(plzVerwaltung()));
    QObject::connect(ui->searchButton, SIGNAL(clicked()), SLOT(suchen()));
    QObject::connect(ui->actionNeuer_Kontakt, SIGNAL(triggered()), SLOT(neuerKontakt()));
    QObject::connect(ui->actionVerwaltung_Postleitzahlen, SIGNAL(triggered()), SLOT(plzVerwaltung()));
    QObject::connect(ui->actionVerlassen, SIGNAL(triggered()), SLOT(verlassen()));
    QObject::connect(ui->dbView, SIGNAL(clicked(QModelIndex)), SLOT(editKontakt(QModelIndex)));

    sql = new QSqlQueryModel();
    // DB-Anzeigen
    sqlquery(false);
}

MemberWindow::~MemberWindow()
{
    delete ui;
    delete sql;
}

void MemberWindow::neuerKontakt()
{
    MemberDialog perwindow;
    // Modales Window:
    // Es ist das oberste Window
    // alle anderen Windows sind nicht bedienbar
    perwindow.setModal(true);
    perwindow.show();
    perwindow.exec();

    // hier wurde das Window wieder geschlossen
    // Update der MemberDialogenliste
    sqlquery(false);
}

void MemberWindow::editKontakt(QModelIndex index)
{
    // Zeile in der Tableview, auf die geklickt wurde
    int row = index.row();
    // wir holen mit der Zeile die versteckte PId heraus
    int pid = ui->dbView->model()->index(row, 0).data().toInt();

    // MemberDialogen - Window starten
    MemberDialog perwindow(this, pid);
    // Modales Window:
    // Es ist das oberste Window
    // alle anderen Windows sind nicht bedienbar
    perwindow.setModal(true);
    perwindow.show();
    perwindow.exec();

    // hier wurde das Window wieder geschlossen
    // Update der MemberDialogenliste
    sqlquery(false);
}

void MemberWindow::plzVerwaltung()
{

}

void MemberWindow::suchen()
{
    sqlquery(true);
}

void MemberWindow::verlassen()
{
    this->close();
}

void MemberWindow::sqlquery(bool filter)
{
    QString query = "select PId,PName,PAdr,PTelnr,PlzNummer,PlzOrt from Personen \
                     join Plz on PPlzFK=PlzId";
    if (filter)
    {
        QString name = ui->searchTextEdit->text();
        if (!name.isEmpty())
            query += " where PName like '" + name + "%'";
    }
    sql->setQuery(query);
    sql->setHeaderData(0, Qt::Horizontal, "Id");
    sql->setHeaderData(1, Qt::Horizontal, "Name");
    sql->setHeaderData(2, Qt::Horizontal, "Adresse");
    sql->setHeaderData(3, Qt::Horizontal, "Telnr");
    sql->setHeaderData(4, Qt::Horizontal, "Plz");
    sql->setHeaderData(5, Qt::Horizontal, "Ort");

    // Verbinden des Models mit der View
    ui->dbView->setModel(sql);
    // Id unterdrücken
    ui->dbView->hideColumn(0);
}

