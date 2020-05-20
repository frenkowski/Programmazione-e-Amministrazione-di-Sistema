#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>

#include <QtCharts>
using namespace QtCharts;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /**
     * @brief Metodo per l'apertura e la conseguente lettura del file "data.txt".
     * Non è stata data la possibilità all'utente di specificare il filename poichè non richiesto dalla traccia.
     * Il contenuto del file trasferito nella QList rows.
     */
    void open();

    /**
     * @brief Metodo usato durante il DEBUG per verificare la correttezza dei dati letti da file.
     */
    void print();

private slots:
    void on_comboBox_currentTextChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;

    QList<QString> rows;    ///< Lista contenente la regione, il range età, il numero uomini e il numero donne letti per ogni riga

    int totale_uomini;      ///< Variabile necessaria per poter calcolare il totale degli uomini per ogni regione
    int totale_donne;       ///< Variabile necessaria per poter calcolare il totale delle donne per ogni regione

    QChart *u_chart;            ///< Chart relativo agli uomini
    QPieSeries *u_series;       ///< Fette del grafico, proporzionali al range d'età, riferite agli uomini
    QChartView *u_chartView;    ///< View del grafico relativo agli uomini

    QChart *d_chart;            ///< Chart relativo alle donne
    QPieSeries *d_series;       ///< Fette del grafico, proporzionali al range d'età, riferite alle donne
    QChartView *d_chartView;    ///< View del grafico relativo alle donne

    /**
     * @brief Metodo per inizializzare la tabella.
     * Usato ad ogni cambiamento della regione.
     * @param title Regione selezionata
     */
    void initializationTable(QString title);

    /**
     * @brief Metodo per popolare la tabella.
     * @param reg Regione selezionata
     */
    void popolateTable(QString reg);

    /**
     * @brief Metodo per inizializzare i grafici.
     * Usato ad ogni cambiamento della regione.
     */
    void initializationChart();

    /**
     * @brief Metodo usato per popolare i grafici.
     * @param reg Regione selezionata
     */
    void popolateChart(QString reg);
};

#endif // MAINWINDOW_H
