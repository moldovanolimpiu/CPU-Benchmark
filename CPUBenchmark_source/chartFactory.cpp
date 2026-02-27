
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLogValueAxis>
#include <QPixmap>
#include <QFileDialog>
#include <QImage>
#include <QPainter>
#include <QStandardPaths>



QChartView* makeChart(const QVector<float>& y_val,const QVector<int>& x_val, const QString& title, const QString& x_label, const QString& y_label, bool time){
    QLineSeries* series = new QLineSeries();

    Q_ASSERT(x_val.size() == y_val.size());

    for(int i = 0; i < y_val.size(); i++){
        series->append(x_val[i], y_val[i]);
    }

    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(title);
    QValueAxis* x_axis = new QValueAxis();
    x_axis->setTitleText(x_label);
    x_axis->setRange(x_val.first(),x_val.last());
    x_axis->setTickCount(x_val.size());
    x_axis->setLabelFormat("%d");
    x_axis->setGridLineVisible(true);
    QValueAxis* y_axis = new QValueAxis();
    y_axis->setTitleText(y_label);
    y_axis->setGridLineVisible(true);
    if(time)
        y_axis->setLabelFormat("%f");
    else
        y_axis->setLabelFormat("%.2f");

    chart->addAxis(x_axis, Qt::AlignBottom);
    chart->addAxis(y_axis, Qt::AlignLeft);
    series->attachAxis(x_axis);
    series->attachAxis(y_axis);

    QChartView* finalChart = new QChartView(chart);
    finalChart->setRenderHint(QPainter::Antialiasing);
    return finalChart;
}


QChartView* makeChartLog(const QVector<float>& y_val,const QVector<int>& x_val, const QString& title, const QString& x_label, const QString& y_label, bool time){
    QLineSeries* series = new QLineSeries();

    //Q_ASSERT(x_val.size() == y_val.size());

    for(int i = 0; i < y_val.size(); i++){
        series->append(x_val[i], y_val[i]);
    }

    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(title);
    QLogValueAxis* x_axis = new QLogValueAxis();
    x_axis->setTitleText(x_label);
    x_axis->setRange(x_val.first(),x_val.last());
    x_axis->setBase(2);
    x_axis->setLabelFormat("%d");
    x_axis->setMinorTickCount(0);
    x_axis->setGridLineVisible(true);
    QValueAxis* y_axis = new QValueAxis();
    y_axis->setTitleText(y_label);
    y_axis->setGridLineVisible(true);
    if(time)
        y_axis->setLabelFormat("%f");
    else
        y_axis->setLabelFormat("%.2f");

    chart->addAxis(x_axis, Qt::AlignBottom);
    chart->addAxis(y_axis, Qt::AlignLeft);
    series->attachAxis(x_axis);
    series->attachAxis(y_axis);

    QChartView* finalChart = new QChartView(chart);
    finalChart->setRenderHint(QPainter::Antialiasing);
    return finalChart;
}

QChartView* makeChartLongLong(const QVector<long long>& y_val,const QVector<int>& x_val, const QString& title, const QString& x_label, const QString& y_label){
    QLineSeries* series = new QLineSeries();

    Q_ASSERT(x_val.size() == y_val.size());

    for(int i = 0; i < y_val.size(); i++){
        series->append(x_val[i], y_val[i]);
    }

    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(title);

    QValueAxis* x_axis = new QValueAxis();
    x_axis->setTitleText(x_label);
    x_axis->setRange(x_val.first(),x_val.last());
    x_axis->setTickCount(x_val.size());
    x_axis->setLabelFormat("%d");
    x_axis->setGridLineVisible(true);
    QValueAxis* y_axis = new QValueAxis();
    y_axis->setTitleText(y_label);
    y_axis->setGridLineVisible(true);
    y_axis->setLabelFormat("%lld");

    chart->addAxis(x_axis, Qt::AlignBottom);
    chart->addAxis(y_axis, Qt::AlignLeft);
    series->attachAxis(x_axis);
    series->attachAxis(y_axis);

    QChartView* finalChart = new QChartView(chart);
    finalChart->setRenderHint(QPainter::Antialiasing);
    return finalChart;
}

QChartView* makeChartLongLongLog(const QVector<long long>& y_val,const QVector<int>& x_val, const QString& title, const QString& x_label, const QString& y_label){
    QLineSeries* series = new QLineSeries();

    Q_ASSERT(x_val.size() == y_val.size());

    for(int i = 0; i < y_val.size(); i++){
        series->append(x_val[i], y_val[i]);
    }

    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(title);

    QLogValueAxis* x_axis = new QLogValueAxis();
    x_axis->setTitleText(x_label);
    x_axis->setRange(x_val.first(),x_val.last());
    x_axis->setBase(2);
    x_axis->setLabelFormat("%d");
    x_axis->setMinorTickCount(0);
    x_axis->setGridLineVisible(true);
    QValueAxis* y_axis = new QValueAxis();
    y_axis->setTitleText(y_label);
    y_axis->setGridLineVisible(true);
    y_axis->setLabelFormat("%lld");

    chart->addAxis(x_axis, Qt::AlignBottom);
    chart->addAxis(y_axis, Qt::AlignLeft);
    series->attachAxis(x_axis);
    series->attachAxis(y_axis);

    QChartView* finalChart = new QChartView(chart);
    finalChart->setRenderHint(QPainter::Antialiasing);
    return finalChart;
}

QChartView* makeChartDouble(const QVector<double>& y_val,const QVector<int>& x_val, const QString& title, const QString& x_label, const QString& y_label, bool time){
    QLineSeries* series = new QLineSeries();

    Q_ASSERT(x_val.size() == y_val.size());

    for(int i = 0; i < y_val.size(); i++){
        series->append(x_val[i], y_val[i]);
    }

    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(title);
    QValueAxis* x_axis = new QValueAxis();
    x_axis->setTitleText(x_label);
    x_axis->setRange(x_val.first(),x_val.last());
    x_axis->setTickCount(x_val.size());
    x_axis->setLabelFormat("%.0f");
    x_axis->setGridLineVisible(true);
    QValueAxis* y_axis = new QValueAxis();
    y_axis->setTitleText(y_label);
    y_axis->setGridLineVisible(true);
    if(time)
        y_axis->setLabelFormat("%.6f");
    else
        y_axis->setLabelFormat("%.2f");

    chart->addAxis(x_axis, Qt::AlignBottom);
    chart->addAxis(y_axis, Qt::AlignLeft);
    series->attachAxis(x_axis);
    series->attachAxis(y_axis);

    QChartView* finalChart = new QChartView(chart);
    finalChart->setRenderHint(QPainter::Antialiasing);
    return finalChart;
}


QChartView* makeChartLogDouble(const QVector<double>& y_val,const QVector<int>& x_val, const QString& title, const QString& x_label, const QString& y_label, bool time){
    QLineSeries* series = new QLineSeries();

    //Q_ASSERT(x_val.size() == y_val.size());

    for(int i = 0; i < y_val.size(); i++){
        series->append(x_val[i], y_val[i]);
    }

    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(title);
    QLogValueAxis* x_axis = new QLogValueAxis();
    x_axis->setTitleText(x_label);
    x_axis->setBase(2);
    x_axis->setLabelFormat("%.0f");
    x_axis->setMinorTickCount(0);
    x_axis->setGridLineVisible(true);
    x_axis->setRange(x_val.first(),x_val.last());
    QValueAxis* y_axis = new QValueAxis();
    y_axis->setTitleText(y_label);
    y_axis->setGridLineVisible(true);
    if(time)
        y_axis->setLabelFormat("%.6f");
    else
        y_axis->setLabelFormat("%.2f");
    chart->addAxis(x_axis, Qt::AlignBottom);
    chart->addAxis(y_axis, Qt::AlignLeft);
    series->attachAxis(x_axis);
    series->attachAxis(y_axis);


    QChartView* finalChart = new QChartView(chart);
    finalChart->setRenderHint(QPainter::Antialiasing);
    return finalChart;
}

void saveChart(QChartView* chart, QString filename, QWidget* parent){
    QString base_dir = QDir(QCoreApplication::applicationDirPath()).filePath("./charts");
    QDir().mkpath(base_dir);
    qInfo() << base_dir;

    QDir().mkpath(base_dir);

    QString file_path = base_dir + "/" + filename + ".png";

    QPixmap pixmap(1200, 800);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    chart->render(&painter);
    painter.end();

    pixmap.save(file_path, "PNG");
}




