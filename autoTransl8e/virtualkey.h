#ifndef VIRTUALKEY_H
#define VIRTUALKEY_H

#include <QWidget>

namespace Ui {
class virtualkey;
}

class virtualkey : public QWidget
{
    Q_OBJECT

public:
    explicit virtualkey(QWidget *parent = 0);
    ~virtualkey();

private:
    Ui::virtualkey *ui;
};

#endif
