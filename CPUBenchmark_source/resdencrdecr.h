#ifndef RESDENCRDECR_H
#define RESDENCRDECR_H

#include <QDialog>
#include "encrDecr.h"

namespace Ui {
class RESDEncrdecr;
}

class RESDEncrdecr : public QDialog
{
    Q_OBJECT

public:
    explicit RESDEncrdecr(QWidget *parent = nullptr);
    ~RESDEncrdecr();
    void setResults(const encryptionDecryptionInfo& result);

private:
    Ui::RESDEncrdecr *ui;
};

#endif // RESDENCRDECR_H
