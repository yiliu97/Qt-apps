#include "newbutton.h"
#include <QPushButton>
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>
#include <QApplication>

newButton::newButton(QWidget *parent):QPushButton(parent)
{
    //connect clicked() signal with slot function
    connect(this,SIGNAL(clicked()),this,SLOT(button_redirect()));
}

void newButton::button_redirect()
{
    //define a QKeyEvent
    QKeyEvent *keyevent;
    //get the value of the button pressed
    QString buf=this->text();

    int key=buf.toInt();

    //redirect some special keys
    if(buf=="Sp")//space
        keyevent=new QKeyEvent(QEvent::KeyPress,Qt::Key_Space,Qt::NoModifier," ");
    else if(buf=="<--") //backspace
        keyevent=new QKeyEvent(QEvent::KeyPress,Qt::Key_Backspace,Qt::NoModifier,buf);
    else if(buf=="En") //enter
        keyevent=new QKeyEvent(QEvent::KeyPress,Qt::Key_Enter,Qt::NoModifier,buf);
    else
        keyevent=new QKeyEvent(QEvent::KeyPress,key,Qt::NoModifier,buf);
    //post the event
    QApplication::postEvent(QApplication::focusWidget(),keyevent);

}
