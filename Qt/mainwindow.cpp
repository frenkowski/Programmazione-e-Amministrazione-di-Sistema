#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

#include <QFile>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Qt");

    ui->tableWidget->verticalHeader()->setVisible(false);

    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Età"));
    ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Maschi"));
    ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Femmine"));
    // inizializzazione e visualizzazione tabella all'avvio del programma

    u_chart = new QChart;
    u_chart->setTitle("Maschi");
    u_series = new QPieSeries();
    u_chartView = new QChartView(u_chart);

    d_chart = new QChart;
    d_chart->setTitle("Femmine");
    d_series = new QPieSeries();
    d_chartView = new QChartView(d_chart);

    ui->u_gridLayout->addWidget(u_chartView);
    ui->d_gridLayout->addWidget(d_chartView);
    // inizializzazione e visualizzazione grafici all'avvio del programa
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::open() {
    QString filename = "data.txt";
    if (filename.isEmpty())
        return;
    else {
        QFile file(filename);

        if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
            QMessageBox::critical(this, tr("Unable to open file"),
                                  file.errorString());
            return;
        }
        // Leggo il testo dal file
        QTextStream readData(&file);
        QString fileLine = readData.readLine();

        while(fileLine!="<END>") {
            QStringList tmp = fileLine.split(" ");  // ogni riga del file equivale ad una lista di stringhe separate da uno spazio
            rows.append(tmp);                       // nell'ordine abbiamo regione, range d'età, numero uomini e numero donne

            fileLine = readData.readLine(); // leggo la riga successiva
        }

        file.close();
    }
}

void MainWindow::print() {
    // la lista rows avrà come elementi consecutivi la regione, il range d'età, il numero uomini e il numero di donne
    // una quaterna di elementi corrisponderanno quindi ad una riga del file letto
    std::cout << "Regione\t\t\t" << "Range Eta'\t\t\t" << "Numero Uomini\t\t\t" << "Numero Donne\t\t\t";
    for(int i=0; i<rows.size(); i+=4) {
        std::cout << rows.at(i).toLocal8Bit().constData() << "\t\t\t";
        std::cout << rows.at(i+1).toLocal8Bit().constData() << "\t\t\t";
        std::cout << rows.at(i+2).toLocal8Bit().constData() << "\t\t\t";
        std::cout << rows.at(i+3).toLocal8Bit().constData() << "\t\t\t";
        std::cout << std::endl;
    }
}

void MainWindow::initializationTable(QString title="Select region") {
    totale_donne = 0;
    totale_uomini = 0;  // inizializzazione variabili intere

    ui->label->setText("<b>"+title+"<\b>"); // RichText

    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);    // rimozione delle righe della tabella relative alla regione precedente
    ui->tableWidget->verticalHeader()->setVisible(false);

    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Età"));
    ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Maschi"));
    ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Femmine"));   // intestazione colonne
}

void MainWindow::popolateTable(QString reg) {
    for(int i=0; i<rows.size(); i+=4) {
        if(rows.at(i)==reg) {   // inserisco nella tabella solo gli elementi della regione selezionata
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());

            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,
                                     0,
                                     new QTableWidgetItem(rows.at(i+1)));   // prima colonna

            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,
                                     1,
                                     new QTableWidgetItem(rows.at(i+2)));   // seconda colonna
            totale_uomini+=rows.at(i+2).toInt();    // aggiorno il totale degli uomini

            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,
                                     2,
                                     new QTableWidgetItem(rows.at(i+3)));   // terza colonna
            totale_donne+=rows.at(i+3).toInt();     // aggiorno il totale degli uomini
        }
    }
    // solo se è stata selezionata effettivamente una regione mostro il totale degli uomini e il totale delle donne
    if(reg!="Select region") {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());

        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,
                                 0,
                                 new QTableWidgetItem("Totale"));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,
                                 1,
                                 new QTableWidgetItem(QString::number(totale_uomini)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,
                                 2,
                                 new QTableWidgetItem(QString::number(totale_donne)));
    }
}

void MainWindow::initializationChart() {
    delete u_chart;
    delete u_series;
    delete u_chartView;

    delete d_chart;
    delete d_series;
    delete d_chartView; // rimozione degli elementi dei grafici relativi alla regione precedente

    u_chart = new QChart;
    u_series = new QPieSeries();

    u_chart->setTitle("Maschi");
    u_chart->addSeries(u_series);
    u_chart->legend()->setAlignment(Qt::AlignRight);

    u_chartView = new QChartView(u_chart);
    u_chartView->setRenderHint(QPainter::Antialiasing);
    u_chart->setAnimationOptions(QChart::AllAnimations);    // inizializzazione per il grafico relativo agli uomini

    d_chart = new QChart;
    d_series = new QPieSeries();

    d_chart->setTitle("Femmine");
    d_chart->addSeries(d_series);
    d_chart->legend()->setAlignment(Qt::AlignRight);

    d_chartView = new QChartView(d_chart);
    d_chartView->setRenderHint(QPainter::Antialiasing);
    d_chart->setAnimationOptions(QChart::AllAnimations);    // inizializzazione per il grafico relativo alle donne
}

void MainWindow::popolateChart(QString reg) {
    for(int i=0; i<rows.size(); i+=4) {
        if(rows.at(i)==reg) {
            u_series->append(rows.at(i+1), rows.at(i+2).toInt()*100/totale_uomini); // uomini per range età in proporzione al totale degli uomini
            d_series->append(rows.at(i+1), rows.at(i+3).toInt()*100/totale_donne);  // donne per range età in proporzione al totale delle donne
        }
    }

    ui->u_gridLayout->addWidget(u_chartView);
    ui->d_gridLayout->addWidget(d_chartView);
}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    initializationTable(arg1);
    popolateTable(arg1);    // inizializzo e popolo la tabella

    initializationChart();
    popolateChart(arg1);    // inizializo e popolo i grafici

}
