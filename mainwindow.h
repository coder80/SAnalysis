#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QHBoxLayout>
#include <math.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_spectrogram.h>
#include <qwt_color_map.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_renderer.h>
#include <qprinter.h>
#include <qprintdialog.h>
#include <qwt_scale_draw.h>
#include <qwt_scale_widget.h>
#include <qwt_plot_layout.h>
#include <qwt_matrix_raster_data.h>
#include <fftw3.h>
#include <complex>
const double pi = 3.1415926535897932384626433832795;

long double min(std::vector<std::vector<long double> > x);
long double max(std::vector<std::vector<long double> > x);
namespace Ui {
    class MainWindow;

}
class Plot: public QwtPlot
{
    Q_OBJECT

public:
    Plot(QWidget * = NULL);

public Q_SLOTS:
    void showContour(bool on);
    void showSpectrogram(bool on);
    void setDataX(std::vector<long double> vec);
    void setDataY(std::vector<long double> vec);
    void setDataZ(std::vector<std::vector<long double> > vec);
    void setData();
#ifndef QT_NO_PRINTER
    void printPlot();
#endif

private:
    QwtPlotSpectrogram *d_spectrogram;

    std::vector<long double> vec1,vec2;
    std::vector<std::vector<long double> > vec3;
};
class Graph : public QMainWindow
{
  Q_OBJECT
public:
    Graph(QWidget* parent = 0);
    ~Graph();
    void setVecX(std::vector<long double>& X);
    void setVecY(std::vector<long double>& Y);
    void setData();
    void setAxis(QString nameX,QString nameY);
    QHBoxLayout* layout;
protected:
    //void changeEvent(QEvent* e);
private:

    std::vector<long double> vecX,vecY;
   QwtPlot* plot;
   QwtPlotCurve* curve;
    double* X,*Y;
    QString NameX,NameY;
   QString title;
};
class GraphP : public QMainWindow
{
public:
    GraphP(QWidget* parent = 0);
    ~GraphP();
    void setVecX(std::vector<long double>& X);
    void setVecY(std::vector<long double>& Y);
    void setVecZ(std::vector<std::vector<long double> >& Z);
    void setData();
    void setAxis(QString nameX, QString nameY);
    QHBoxLayout* layout;
private:
    std::vector<long double> vecX, vecY;
    std::vector<std::vector<long double> > vecZ;
    QwtPlot* plot;
    QwtPlotCurve* curve;
    Plot* waveplot;
    double* X, *Y, *Z;
    QString NameX, NameY, title;
    QwtPlotSpectrogram* spectr;
};
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    QwtPlot* plot;
    std::vector<long double> vec,vec_fft1,vec_fft2,vec_fft,vec_fft3,vec_fft0,wt;
    std::vector<std::vector<long double> > vec1,vec2;
    Graph* gr1,*gr2, *gr;
    GraphP* gr3,*gr4,*gr5, *r1;
    long double win_1(int t, int N);
    long double mhat(long double t);
    long double morler(long double t, long double alpha);
    long double morlei(long double t, long double alpha);
    int fft1(std::vector<long double> vec, std::vector<long double>& vec1, std::vector<long double>& vec2);
    int fft(std::vector<long double> vec, std::vector<long double>& vec1, std::vector<long double>& vec2);
    int fftback(std::vector<long double> vec1, std::vector<long double> vec2, std::vector<long double>& vec);
    int dwt1(std::vector<long double> vec, std::vector<std::vector<long double> >& vec1, std::vector<long double> a, std::vector<long double> b, long double T);
    int dwt2(std::vector<long double> vec, std::vector<std::vector<long double> >& vec1, std::vector<long double> a, std::vector<long double> b, long double T);
private slots:
    void on_pushButton_9_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // MAINWINDOW_H
