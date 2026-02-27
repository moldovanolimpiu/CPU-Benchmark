#pragma once
#ifndef RESDMEMTRANSFER_H
#define RESDMEMTRANSFER_H

#include <QDialog>
#include "memTransfer.h"

namespace Ui {
class RESDMemtransfer;
}

class RESDMemtransfer : public QDialog
{
    Q_OBJECT

public:
    explicit RESDMemtransfer(QWidget *parent = nullptr);
    ~RESDMemtransfer();
    void setResults(const MemTransferInfo& result);

private:
    Ui::RESDMemtransfer *ui;
};

#endif // RESDMEMTRANSFER_H
