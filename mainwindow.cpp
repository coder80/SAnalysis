#include "mainwindow.h"
#include "ui_mainwindow.h"

long double min(std::vector<std::vector<long double> > x)
{
    int N = x.size();
    long double a = x[0][0];
    for (int i = 0; i < N; i++)
    {
        int M = x[i].size();
        for (int j = 0; j < M; j++)
        {
            if (a > x[i][j]) a = x[i][j];
        }
    }
    return a;
}
long double max(std::vector<std::vector<long double> > x)
{
    int N = x.size();
    long double a = x[0][0];
    for (int i = 0; i < N; i++)
    {
        int M = x[i].size();
        for (int j = 0; j < M; j++)
        {
            if (a < x[i][j]) a = x[i][j];
        }
    }
    return a;
}

class MyZoomer: public QwtPlotZoomer
{
public:
    MyZoomer(QwtPlotCanvas *canvas):
        QwtPlotZoomer(canvas)
    {
        setTrackerMode(AlwaysOn);
    }

    virtual QwtText trackerTextF(const QPointF &pos) const
    {
        QColor bg(Qt::white);
        bg.setAlpha(200);
        QwtText text = QwtPlotZoomer::trackerTextF(pos);
        text.setBackgroundBrush( QBrush( bg ));
        return text;
    }
};
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //QwtPlotCurve *curve1 = new QwtPlotCurve("Curve 1");
        r1 = NULL;
        gr = NULL;
        gr1 = NULL;
        gr2 = NULL;
        gr3 = NULL;
        gr4 = NULL;
        gr5 = NULL;
        ui->lineEdit->setText("0.0");
        ui->lineEdit_2->setText("0");
        ui->lineEdit_3->setText("0");
        ui->lineEdit_4->setText("2");
        ui->lineEdit_5->setText("2");
        ui->lineEdit_6->setText("100");
        ui->lineEdit_7->setText("100");
        ui->lineEdit_8->setText("5");
        ui->lineEdit_9->setText("5");

        QPixmap pix("pic1.png");
        QPixmap pix1("pic2.png");
        QPalette pal;
        pal.setBrush(QPalette::Window,QBrush(pix1));
        //pix.scaled(100,100,Qt::IgnoreAspectRatio,Qt::FastTransformation);
        ui->label_11->setPixmap(pix);
        ui->label_11->setScaledContents(true);
        //ui->pushButton_2->setEnabled(false);




    }

MainWindow::~MainWindow()
{
    delete ui;
    delete gr, gr1, gr2, gr3, gr4, gr5, r1;
    if (r1 != NULL) delete r1;

}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if (vec.size() == 0) return;
    vec_fft1.clear();
    vec_fft2.clear();
    vec_fft3.clear();
    vec_fft0.clear();
    vec_fft.clear();
    vec1.clear();
    wt.clear();
    double omega = ui->lineEdit->text().toDouble();
    double omega1 = omega - omega/vec.size();
    ui->lineEdit_2->setText(QString::number(omega1));
    
    int N1 = vec.size() - 1;
    int M1 = vec.size();
    for (int i = 0; i < vec.size(); i++)
    {
        double x = double(i);
        vec_fft.push_back(x);
    }
    for (int i = 0; i < M1; i++)
    {
        double x;
        if (omega != 0)  x = i*omega1/M1;
        else x = double(i);
        wt.push_back(x);;
    }
    if (gr != NULL) delete gr;
    if (gr1 != NULL) delete gr1;
    if (gr2 != NULL) delete gr2;
    //gr = new Graph(this);
    gr1 = new Graph(this);
    gr2 = new Graph(this);

    //gr->setAxis("X","Y");

    //gr->show();
    //vec_fft.clear();
    /*for (int i = 0; i < vec.size(); i++)
    {
        long double x = sqrt(vec_fft1[i]*vec_fft1[i] + vec_fft2[i]*vec_fft2[i])/ vec.size();
        vec_fft3.push_back(x);
    }
    */
    gr2->setVecX(vec_fft);
    gr2->setVecY(vec);
    gr2->setData();
    gr2->setAxis("I","Xi");
    gr2->show();
   // gr->setVecX(wt);
    //gr->setVecY(vec_fft3);
    //gr->setData();

       vec_fft1.clear();
       vec_fft2.clear();
       fft(vec,vec_fft1,vec_fft2);
       vec_fft3.clear();
       /*for(int i = vec_fft1.size()/2; i < vec_fft1.size(); i++)
       {
           vec_fft1[i] = 0;
       }
       for(int i = 1; i < vec_fft1.size()/2; i++)
       {
           vec_fft1[i] *= 2;
       }
       */
       vec_fft0.clear();
       for (int i = 1; i < vec_fft1.size(); i++)
       {
           long double x = 2*sqrt(vec_fft1[i]*vec_fft1[i] + vec_fft2[i]*vec_fft2[i])/(vec_fft1.size());
           //long double x = sqrt(vec_fft1[i]*vec_fft1[i] + vec_fft2[i]*vec_fft2[i]);
           vec_fft0.push_back(x);
       }
       gr1->setVecX(wt);
       gr1->setVecY(vec_fft0);
       gr1->setData();
       gr1->show();



}

void MainWindow::on_pushButton_clicked()
{
    QString FileName = QFileDialog::getOpenFileName(this,tr("Open File"),"",tr("Text File (*.txt)"));
    QFile f(FileName);
    char s[100];
    QString SS;
    long double X;
    vec.clear();
    if(!f.open(QIODevice::ReadOnly)){return;}
    while (!f.atEnd())
    {
        int c = f.readLine(s,100);
        SS = s;
        //sscanf(SS.toStdString().c_str(),"%f ",&X);
        X = SS.toDouble();
        vec.push_back(X);

    }
    ui->lineEdit_2->setText(QString::number(vec.size()));
    ui->lineEdit_3->setText(QString::number(0));
}

int MainWindow::fft1(std::vector<long double> vec, std::vector<long double>& vec1, std::vector<long double>& vec2)
{
    double X = 0;
    int N = vec.size();
    for(int i = 0; i < N; i++)
    {
        for(int k = 0; k < N; k++)
        {
            X += vec[k]*cos(2*pi*i*k/N);
        }
        vec1.push_back(X);
        X = 0;
    }
    X = 0;
    for(int i = 0; i < N; i++)
    {
        for(int k = 0; k < N; k++)
        {
            X += -vec[k]*sin(2*pi*i*k/N);
        }
        vec2.push_back(X);
        X = 0;
    }
    return 1;
}
int MainWindow::fft(std::vector<long double> vec, std::vector<long double>& vec1, std::vector<long double>& vec2)
{

    int N = vec.size();
    double* x = (double*)fftw_malloc(sizeof(double) * N);
    fftw_complex* out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*N);
    for (int i = 0; i < N; i++)
    {
        x[i] = double(vec[i]);

    }
    for (int i = 0; i < N; i++)
    {
        out[i][0] = 0.0;
        out[i][1] = 0.0;
    }
    //memset(out,0,sizeof(out)*N);
    fftw_plan plan = fftw_plan_dft_r2c_1d(N, x, out, FFTW_ESTIMATE);
    fftw_execute(plan);
    
    for (int i = 0; i < N; i++)
    {

        vec1.push_back(out[i][0]);
        
        
    }
    for(int i = 0; i < N; i++)
    {
        vec2.push_back(out[i][1]);
    }
    fftw_destroy_plan(plan);
    fftw_free(x);
    fftw_free(out);
    return 0;
}
int MainWindow::fftback(std::vector<long double> vec1, std::vector<long double> vec2, std::vector<long double>& vec)
{
    int N = vec1.size();
    double* x = (double*)fftw_malloc(sizeof(double)*N);
    fftw_complex* in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*N);
    for (int i = 0; i < N; i++)
    {
        in[i][0] = vec1[i];
        in[i][1] = vec2[i];
    }
    fftw_plan plan = fftw_plan_dft_c2r_1d(N, in, x, FFTW_ESTIMATE);
    fftw_execute(plan);
    for (int i = 0; i < N; i ++)
    {
        x[i] = x[i];
        vec.push_back(x[i]);
    }
    fftw_destroy_plan(plan);
    fftw_free(x);
    fftw_free(in);
    return 0;
}
long double MainWindow::mhat(long double t)
{
    long double x = (1 - t*t)*exp(-t*t/2);
    return x;
}
long double MainWindow::morler(long double t, long double alpha)
{
    long double k = 2*pi;
    long double x = exp(-t*t/(alpha*alpha))*cos(2*pi*t);
    return x;
}
long double MainWindow::morlei(long double t, long double alpha)
{
    long double k = 2*pi;
    long double x = exp(-t*t/(alpha*alpha))*sin(2*pi*t);
    return x;
}
int MainWindow::dwt1(std::vector<long double> vec, std::vector<std::vector<long double> >& vec1, std::vector<long double> a, std::vector<long double> b, long double T)
{
    int N = vec.size();
    double x = 0.0;
    int N1 = a.size();
    int N2 = b.size();
    long double n = 0;
    long double x1 = 0.0;
    long double t1 = 0;
    long double h1 = T/(N - 1);
    long double B = 2;
    std::vector<long double> vec2;
    for (int i = 0; i < N1; i++){
        vec1.push_back(vec2);
        for (int j = 0; j < N2; j++)
        {
            x = 0.0;
            t1 = 0;
            for (int k = 0; k < N; k ++)
            {

                t1 += h1;
                x += exp((-1.0/B)*((t1 - b[j])/a[i])*((t1 - b[j])/a[i]));
            }
            n = x;
            x = 0.0;
            t1 = 0;
            for (int k = 0; k < N; k++)
            {
                t1 += h1;
                x += vec[k]*mhat((t1 - b[j])/a[i]);
            }
            x /= n;
            x = x*x;
            n = 0;
            vec1[i].push_back(x);
        }
    }
    return 1;
}
int MainWindow::dwt2(std::vector<long double> vec, std::vector<std::vector<long double> >& vec1, std::vector<long double> a, std::vector<long double> b, long double T)
{
    int N = vec.size();
    double x = 0.0;
    int N1 = a.size();
    int N2 = b.size();
    long double n = 0;
    long double x1 = 0.0;
    long double t1 = 0;
    long double y = 0;
    long double h1 = T/(N - 1);
    long double alpha = 1.5;
    long double B = alpha*alpha;
    std::vector<long double> vec2;
    for (int i = 0; i < N1; i++){
        vec1.push_back(vec2);
        for (int j = 0; j < N2; j++)
        {
            x = 0.0;
            t1 = 0;
            for (int k = 0; k < N; k ++)
            {

                t1 += h1;
                x += exp((-1.0/B)*((t1 - b[j])/a[i])*((t1 - b[j])/a[i]));

            }
            n = x;
            x = 0.0;
            t1 = 0;
            for (int k = 0; k < N; k++)
            {
                t1 += h1;
                x += vec[k]*morler((t1 - b[j])/a[i],alpha);
                y += vec[k]*morlei((t1 - b[j])/a[i],alpha);
            }
            x /= n;
            y /= n;
            x = x*x + y*y;
            //x = fabs(x);
            n = 0;
            vec1[i].push_back(x);
        }
    }
    return 1;
}
long double MainWindow::win_1(int t, int N)
{
    long double x;
    if ((t > 0)&&(t < N - 1))
    {
        x = 1;
    }
    else
    {
        x = 0;
    }
    return x;
}
Graph::Graph(QWidget* parent):
        QMainWindow(parent)
{

    layout = new QHBoxLayout(this);
    title = "Graphic";
    plot = new QwtPlot(this);
    curve = new QwtPlotCurve(title);
    curve->attach(plot);
    curve->setVisible(true);
    ;
    this->setCentralWidget(plot);

    //layout->addWidget(plot);
    //this->setLayout(layout);
    this->setGeometry(10,10,300,300);
    QwtPlotZoomer* zoomer = new MyZoomer(plot->canvas());
    zoomer->setMousePattern(QwtEventPattern::MouseSelect2,
        Qt::RightButton, Qt::ControlModifier);
    zoomer->setMousePattern(QwtEventPattern::MouseSelect3,
        Qt::RightButton);

}
Graph::~Graph()
{
    delete plot,curve;
    delete[] X,Y;
}

void Graph::setVecX(std::vector<long double>& X)
{
    vecX.clear();
    vecX = X;

}
void Graph::setVecY(std::vector<long double>& Y)
{
    vecY.clear();
    vecY = Y;

}
void Graph::setData()
{

    X = new  double[vecX.size() + 5];
    Y = new  double[vecY.size() + 5];

    for(int i = 0; i < vecX.size(); i++)
    {
        X[i] = (double)vecX[i];

    }
    for (int i = 0; i < vecY.size(); i++)
    {
        Y[i] = (double)fabs(vecY[i]);
    }
    curve->setRawSamples(X,Y, vecX.size() - 1);
    curve->setPen(QPen(QColor("green")));


    curve->show();
    //delete[] X;
    //delete[] Y;
}
void Graph::setAxis(QString nameX, QString nameY)
{
    NameX = nameX;
    NameY = nameY;
    plot->setAxisTitle(2,NameX);
    plot->setAxisTitle(0,NameY);
}
GraphP::GraphP(QWidget* parent):
        QMainWindow(parent)
{
    layout = new QHBoxLayout(this);
    title = "Wavelete";
    //plot = new QwtPlot(this);
    //curve = new QwtPlotCurve(title);
    //curve->attach(plot);
    //curve->setVisible(true);
    //this->setCentralWidget(plot);
    this->setGeometry(10,10,800,500);
    waveplot = new Plot(this);


    this->setCentralWidget(waveplot);
}
GraphP::~GraphP()
{
    delete waveplot;
    waveplot = NULL;
    //delete[] X,Y,Z;
}
void GraphP::setVecX(std::vector<long double>& X)
{
    vecX.clear();
    vecX = X;
    waveplot->setDataX(X);
}
void GraphP::setVecY(std::vector<long double>& Y)
{
    vecY.clear();
    vecY = Y;
    waveplot->setDataY(Y);
}
void GraphP::setVecZ(std::vector<std::vector<long double> >& Z)
{
    vecZ.clear();
    vecZ = Z;
    waveplot->setDataZ(Z);
}
void GraphP::setData()
{
    /*X = new  double[vecX.size() + 5];
    Y = new  double[vecY.size() + 5];
    Z = new  double[vecZ.size() + 5];
    for (int i = 0; i < vecX.size(); i++)
    {
        X[i] = (double)vecX[i];
    }
    for (int i = 0; i < vecY.size(); i++)
    {
        Y[i] = (double)vecY[i];
    }
    for (int i = 0; i < vecZ.size(); i++)
    {
        Y[i] = (double)fabs(vecZ[i]);
    }
    curve->setRawSamples(X, Y, vecX.size() - 1);
    curve->setPen(QPen(QColor("green")));
    curve->show();
    */
    waveplot->setData();

}
void GraphP::setAxis(QString nameX, QString nameY)
{
    NameX = nameX;
    NameY = nameY;
    waveplot->setAxisTitle(2, NameX);
    waveplot->setAxisTitle(0, NameY);
}
void MainWindow::on_pushButton_3_clicked()
{
    if (vec.size() == 0) return;
    wt.clear();
    int N = vec.size();
    double omega = ui->lineEdit->text().toDouble();
    double omega1 = omega - omega/N;
    long double a1 = 1;
    long double a2 = 20;
    long double b1 = 1;
    long double b2 = 20;
    std::vector<long double> a;
    std::vector<long double> b;
    for (int i = 0; i < N; i++)
    {
       double x;
       if (omega != 0) x = i*omega1/N;
       else x = double(i);
       wt.push_back(x);
    }
    vec1.clear();

    /*a1 = wt[1] - wt[0];
    a2 = (N - 1)*(wt[1] - wt[0])/2;
    b1 = wt[2] - wt[1];
    b2 = (wt[2] - wt[1])*(N - 1);
    */
    if (omega == 0) omega = 1;
    a1 = fabs(log(2/omega));
    a2 = fabs(log((N - 1)/(2*omega)));
    b1 = 1/omega;
    b2 = (N - 1)/omega;
    int N1 = ui->lineEdit_6->text().toInt();
    int N2 = ui->lineEdit_7->text().toInt();
    long double h1 = 0.0;
    long double h2 = 0.0;

    h1 = (a2 - a1)/(N1 - 1);
    h2 = (b2 - b1)/(N2 - 1);
    double x = 0.0;
    x = a1;
    a.push_back(x);
    for (int i = 1; i < N1; i++){
        x += h1;
        a.push_back(x);
    }
    x = b1;
    b.push_back(x);
    for (int i = 1; i < N2; i++){
        x += h2;
        b.push_back(x);
    }
    //if (omega == 0) omega = 1;
    if (ui->comboBox->currentIndex() == 0){
        dwt1(vec, vec1,a,b,(N - 1)/omega);}
    if (ui->comboBox->currentIndex() == 1){
        dwt2(vec, vec1,a,b,(N - 1)/omega);}
    long double xx = max(vec1);
    int N3 = vec1.size();

    for (int i = 0; i < N3; i++)
    {
        for (int j = 0; j < vec1[i].size(); j++){
            vec1[i][j] /= xx;
            vec1[i][j] /= 100;
        }
    }


    if (gr3 != NULL) delete gr3;
    gr3 = new GraphP(this);
    gr3->setAxis("time","period");
    gr3->setVecX(b);
    gr3->setVecY(a);
    gr3->setVecZ(vec1);
    gr3->setData();
    //gr1->setData();
    gr3->show();

}

void MainWindow::on_pushButton_4_clicked()
{

   if (vec.size() == 0) return;
   if ((vec_fft1.size() == 0)||(vec_fft2.size() == 0)) return;
   if (gr != NULL) delete gr;
   Graph* gr = new Graph(this);
  vec_fft0.clear();
  int N = vec_fft1.size();
  for (int i = 0; i < N; i++)
  {
      vec_fft1[i] = vec_fft1[i]/N;
      vec_fft2[i] = vec_fft2[i]/N;

  }
  fftback(vec_fft1,vec_fft2,vec_fft0);

  gr->setVecX(vec_fft);
  gr->setVecY(vec_fft0);
  gr->setData();
  gr->show();
}

void MainWindow::on_pushButton_5_clicked()
{
    if (vec.size() == 0) return;
    int N = vec.size();
    std::vector<long double> X,Y;
    long double x;
    long double y;
    int c = ui->lineEdit_8->text().toInt();
    for (int i = 0; i < N - c; i++)
    {
        x = vec[i];
        y = vec[i + c];
        X.push_back(x);
        Y.push_back(y);
    }
    if (gr != NULL) delete gr;
    gr = new Graph(this);
    gr->setVecX(X);
    gr->setVecY(Y);
    gr->setAxis("X","Y");
    gr->setData();
    gr->show();
}

void MainWindow::on_pushButton_6_clicked()
{
    if (vec.size() == 0) return;
    int N = vec.size();
    std::vector<long double> X,Y,X1,X2,Y2;
    std::vector<std::vector<long double> > arr;
    long double x;
    long double y;
    int c = ui->lineEdit_9->text().toInt();
    int M = N - c;
    int a;
    long double e = 1;
    double e1 = 0.5;
    int N1 = e1*N;
    int N2 = N - N1;
    for (int i = 0;i < M; i++)
    {
        x = vec[i];
        y = vec[i + c];
        X.push_back(x);
        Y.push_back(y);
    }
    for (int i = N1;i < M; i++)
    {
        for (int j = N1; j < M; j++)
        {
            x = sqrt((X[i] - X[j])*(X[i] - X[j]) + (Y[i] - Y[j])*(Y[i] - Y[j]));
            if (e > x)
            {
                a = 1;
            }
            else
            {
                a = 0;
            }
            X1.push_back(a);
        }
        arr.push_back(X1);
        X1.clear();
    }
    for (int i = N1; i < M; i++)
    {
        X2.push_back(i - N1);
        Y2.push_back(i - N1);
    }
    if (r1 != NULL) {
        delete r1;
    }
    r1 = new GraphP(this);
    r1->setAxis("i","j");
    r1->setVecX(X2);
    r1->setVecY(Y2);
    r1->setVecZ(arr);
    r1->setData();
    r1->show();
}

void MainWindow::on_pushButton_7_clicked()
{
    double freq1 = ui->lineEdit_2->text().toDouble();
    double freq2 = ui->lineEdit_3->text().toDouble();
    vec_fft1.clear();
    vec_fft2.clear();
    vec_fft3.clear();
    vec_fft0.clear();
    vec_fft.clear();
    vec1.clear();
    wt.clear();
    double omega = ui->lineEdit->text().toDouble();
    double omega1 = omega - omega/vec.size();
    int N1 = vec.size() - 1;
    int M1 = vec.size();
    int N = vec.size();
    for (int i = 0; i < M1; i++)
    {
        double x;
        if (omega != 0)  x = i*omega1/M1;
        else x = double(i);
        wt.push_back(x);
    }
    fft(vec,vec_fft1,vec_fft2);
    for (int i = 0; i < N; i++)
    {
        vec_fft1[i] /= M1;
        vec_fft2[i] /= M1;
        if (wt[i] > freq1){
            vec_fft1[i] = 0;
            vec_fft2[i] = 0;
        }
        if (wt[i] < freq2){
            vec_fft1[i] = 0;
            vec_fft2[i] = 0;
        }
    }

    Graph* gr = new Graph(this);
    vec_fft0.clear();
    fftback(vec_fft1, vec_fft2, vec_fft0);
    gr->setVecX(wt);
    gr->setVecY(vec_fft0);
    gr->setData();
    gr->show();



}

void MainWindow::on_pushButton_8_clicked()
{
    if (vec.size() == 0) return;
    int N = vec.size();
    int M = vec.size();
    std::vector<long double> arr, arr1, re, im, wt1;
    std::vector<std::vector<long double> > vec3;
    wt.clear();
    double omega = ui->lineEdit->text().toDouble();
    double omega1 = omega - omega/N;
    for (int i = 0; i < N; i++)
    {
       double x;
       if (omega != 0) x = i*omega1/N;
       else x = double(i);
       wt.push_back(x);
    }
   vec2.clear();
    if (omega == 0) omega = 1;
    int N1 = N / 400;
    int k = 0;
    for (int i = 0; i < N; i++)
    {
        arr1.clear();
        vec3.push_back(arr1);
        for (int j = 0; j < N; j+=N1)
        {
            vec3[i].push_back(0);
        }
    }
    for (int i = 0; i < N; i+=N1)
    {
        arr.clear();
        arr1.clear();
        re.clear();
        im.clear();
        wt1.push_back(wt[i]);
        vec2.push_back(arr1);
        for (int j = 0; j < N; j++)
        {
            arr.push_back(vec[j]*win_1(j - i, N1));
        }
        fft(arr,re,im);
        for (int j = 0; j < N; j++)
        {
            long double x = sqrt(re[j]*re[j] + im[j]*im[j]);
            vec2[k].push_back(x);
        }
        k++;

    }
    for (int i = 0; i < N; i++)
    {
        k = 0;
        for (int j = 0; j < N; j+=N1)
        {
            vec3[i][k] = vec2[k][i];
            k++;
        }
    }

    if (gr5 != NULL) delete gr5;
    gr5 = new GraphP(this);
    gr5->setAxis("Time", "Freq");
    gr5->setVecX(wt1);
    gr5->setVecY(wt);
    gr5->setVecZ(vec3);
    gr5->setData();
    gr5->show();
}

void MainWindow::on_pushButton_9_clicked()
{

   if (vec.size() == 0) return;
    vec_fft1.clear();
    vec_fft2.clear();
    vec_fft3.clear();
    vec_fft0.clear();
    vec_fft.clear();
    vec1.clear();
    wt.clear();
    double omega = ui->lineEdit->text().toDouble();
    double omega1 = omega - omega/vec.size();
    ui->lineEdit_2->setText(QString::number(omega1));
    fft1(vec, vec_fft1, vec_fft2);
    int N1 = vec.size() - 1;
    int M1 = vec.size();
    for (int i = 0; i < vec.size(); i++)
    {

        double x = double(i);
        vec_fft.push_back(x);
    }
    for (int i = 0; i < M1; i++)
    {
        double x;
        if (omega != 0)  x = i*omega1/M1;
        else x = double(i);
        wt.push_back(x);;
    }
    int N = vec_fft1.size();
    for (int i = 0; i < N; i++)
    {
        long double x = sqrt(vec_fft1[i]*vec_fft1[i] + vec_fft2[i]*vec_fft2[i])/N;
        vec_fft3.push_back(x);
    }
    if (gr != NULL) delete gr;
    gr = new Graph(this);
    gr->setVecX(wt);
    gr->setVecY(vec_fft3);
    gr->setData();
    gr->show();


}
