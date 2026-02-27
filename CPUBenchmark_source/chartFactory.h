#pragma once
#ifndef CHARTFACTORY_H
#define CHARTFACTORY_H
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

QChartView* makeChart(const QVector<float>& y_val,const QVector<int>& x_val, const QString& title, const QString& x_label, const QString& y_label, bool time);
QChartView* makeChartLog(const QVector<float>& y_val,const QVector<int>& x_val, const QString& title, const QString& x_label, const QString& y_label, bool time);
QChartView* makeChartLongLong(const QVector<long long>& y_val,const QVector<int>& x_val, const QString& title, const QString& x_label, const QString& y_label);
QChartView* makeChartLongLongLog(const QVector<long long>& y_val,const QVector<int>& x_val, const QString& title, const QString& x_label, const QString& y_label);
QChartView* makeChartDouble(const QVector<double>& y_val,const QVector<int>& x_val, const QString& title, const QString& x_label, const QString& y_label, bool time);
QChartView* makeChartLogDouble(const QVector<double>& y_val,const QVector<int>& x_val, const QString& title, const QString& x_label, const QString& y_label, bool time);
void saveChart(QChartView* chart, QString filename, QWidget* parent);

#endif // CHARTFACTORY_H
