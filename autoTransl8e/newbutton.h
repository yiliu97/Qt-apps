#ifndef NEWBUTTON_H
#define NEWBUTTON_H
#include <QPushButton>

class newButton : public QPushButton
{
    Q_OBJECT
public:
    newButton(QWidget *parent);
private slots:
    void button_redirect();
};

#endif // NEWBUTTON_H
