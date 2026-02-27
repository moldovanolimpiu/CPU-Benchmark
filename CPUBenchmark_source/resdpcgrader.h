#pragma once
#ifndef RESDPCGRADER_H
#define RESDPCGRADER_H

#include <QDialog>
#include "pcGrader.h"
#include <QChartView>

namespace Ui {
class RESDPcgrader;
}

class RESDPcgrader : public QDialog
{
    Q_OBJECT

public:
    explicit RESDPcgrader(QWidget *parent = nullptr);
    ~RESDPcgrader();
    void setResults(const pcGraderInfo& result);
    void saveChartList();

private:
    Ui::RESDPcgrader *ui;
    QVector<QChartView*> saved_charts;
    QVector<QString> saved_names;
};

#endif // RESDPCGRADER_H
