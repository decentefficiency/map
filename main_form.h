#ifndef TMAINFORM_H
#define TMAINFORM_H

#include <QTimer>
#include <QWidget>
#include <QChart>
#include <QSplineSeries>
#include <QScatterSeries>
#include <QChartView>
#include <QValueAxis>

QT_BEGIN_NAMESPACE
namespace Ui { class TMainForm; }
QT_END_NAMESPACE

using namespace QtCharts;

class TMainForm : public QWidget
{
    Q_OBJECT

    QTimer time;
    double X;
    double Y;
    double V;
    double psi;
    QChart * chart;
    QSplineSeries * trajectoryAUV;
    QScatterSeries * auvPosition;
    QChartView     *  chartView;
    QValueAxis *axisX;
    QValueAxis *axisY;

public:
    TMainForm(QWidget *parent = nullptr);
    ~TMainForm();

private slots:
    void on_btnStart_clicked();
    void on_btnVPlus_clicked();
    void on_btnVMinus_clicked();
    void on_btnPsiPlus_clicked();
    void on_btnPsiMinus_clicked();
    void on_btnLeft_clicked();
    void on_btnRight_clicked();
    void on_btnUp_clicked();
    void on_btnDown_clicked();
    void on_btnClear_clicked();
    void onTimerTimeout();
private:
    Ui::TMainForm *ui;
};
#endif // TMAINFORM_H
