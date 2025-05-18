#include "main_form.h"
#include "ui_main_form.h"
#include <QValueAxis>
#include <math.h>

TMainForm::TMainForm(QWidget *parent)
    : QWidget(parent)    
    , X(0)
    , Y(0)
    , V(100)
    , psi(0)
    , chart(NULL)    
    , trajectoryAUV(NULL)
    , auvPosition(NULL)
    , chartView(NULL)
    , axisX(0)
    , axisY(0)
    , ui(new Ui::TMainForm)
{

    ui->setupUi(this);
    time.setInterval(100);
    connect(&time, &QTimer::timeout, this, &TMainForm::onTimerTimeout);

    chart = new QtCharts::QChart();
    trajectoryAUV = new QtCharts::QSplineSeries(chart);
    auvPosition = new QtCharts::QScatterSeries(chart);

    chart->addSeries(trajectoryAUV);
    chart->addSeries(auvPosition);

    axisX = new QValueAxis();
    axisX->setTitleText("x, м");
    axisX->setLabelFormat("%i");
    axisX->setTickCount(10);
    axisX->setMin(-100);
    axisX->setMax(100);
    chart->addAxis(axisX, Qt::AlignBottom);

    trajectoryAUV->attachAxis(axisX);
    auvPosition->attachAxis(axisX);

    axisY = new QValueAxis();
    axisY->setTitleText("y, м");
    axisY->setLabelFormat("%i");
    axisY->setTickCount(10);
    axisY->setMin(-100);
    axisY->setMax(100);

    chart->addAxis(axisY, Qt::AlignLeft);

    trajectoryAUV->attachAxis(axisY);
    auvPosition->attachAxis(axisY);

    chartView = new QChartView(this);
    chartView->setChart(chart);
    ui->layoutChart->addWidget(chartView);

}

TMainForm::~TMainForm()
{
    delete ui;
}

void TMainForm::onTimerTimeout()
{
  double dt = 1;

  X += dt*0.01*V*cos(psi/57.3);
  Y += dt*0.01*V*sin(psi/57.3);

  trajectoryAUV->append(X, Y);
  auvPosition->clear();
  auvPosition->append(X, Y);

  ui->editV->setText(QString::number(V));
  ui->editCourse->setText(QString::number(psi));
}

void TMainForm::on_btnStart_clicked()
{
    if (time.isActive())
    {
      time.stop();
      ui->btnStart->setText("Запустить");
    } else
    {
      time.start();
      ui->btnStart->setText("Остановить");
    }
}

void TMainForm::on_btnVPlus_clicked()
{
    V += 10;
}

void TMainForm::on_btnVMinus_clicked()
{
    V -= 10;
}

void TMainForm::on_btnPsiPlus_clicked()
{
    if (psi < 360) psi += 10;
    else psi = psi - (psi / 360)*360 + 10;
}


void TMainForm::on_btnPsiMinus_clicked()
{
    if (psi > -360) psi -= 10;
    else psi = psi - (psi / 360)*360 - 10;
}


void TMainForm::on_btnLeft_clicked()
{
    axisX->setMin( axisX->min() - 10);
    axisX->setMax( axisX->max() - 10);
}


void TMainForm::on_btnRight_clicked()
{
    axisX->setMin( axisX->min() + 10);
    axisX->setMax( axisX->max() + 10);
}


void TMainForm::on_btnUp_clicked()
{
    axisY->setMin( axisY->min() + 10);
    axisY->setMax( axisY->max() + 10);
}


void TMainForm::on_btnDown_clicked()
{
    axisY->setMin( axisY->min() - 10);
    axisY->setMax( axisY->max() - 10);
}


void TMainForm::on_btnClear_clicked()
{
      X = 0;
      Y = 0;
      V = 100;
      psi = 0;
      trajectoryAUV->clear();
      auvPosition->clear();
}

