#pragma once
#ifndef RESDMEMACCESS_H
#define RESDMEMACCESS_H

#include <QDialog>
#include "memAccess.h"

namespace Ui {
class RESDMemaccess;
}

class RESDMemaccess : public QDialog
{
    Q_OBJECT

public:
    explicit RESDMemaccess(QWidget *parent = nullptr);
    ~RESDMemaccess();
    void setResults(const AllMemAccessInfo& result);

private:
    Ui::RESDMemaccess *ui;
};

#endif // RESDMEMACCESS_H
