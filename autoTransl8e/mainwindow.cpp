/*
    This app is a desktop software using Baidu Translate API
    Can also be cross-compiled for ARM Linux platform

*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
//MetaEnum
#include <QMetaEnum>
//Network
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
//JSON
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>
//Used to create MD5
#include <QCryptographicHash>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //install event filter for src_text
    ui->src_text->installEventFilter(this);
    ui->widget->hide();
    //connect finished()signal and slot function recv_data()
    connect(&net_manage,&QNetworkAccessManager::finished,this,&MainWindow::recv_data);
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (watched==ui->src_text)
    {
        if(event->type()==QEvent::FocusIn)
        {
            ui->widget->show();
        }
        else if(event->type()==QEvent::FocusOut)
        {
            ui->widget->hide();
        }

    }

    return QMainWindow::eventFilter(watched,event);
}


MainWindow::~MainWindow()
{
    delete ui;
}

//generate the MD5 sign
QString MainWindow::md5_generate(QString src_var)
{
    QString md5;
    QByteArray ba,bb;
    QCryptographicHash md(QCryptographicHash::Md5);
    ba.append(src_var);
    md.addData(ba);
    bb = md.result();
    md5.append(bb.toHex());
    return md5;
}

//convert the language name to the corresponding code
//6 languages are listed in this app
QString MainWindow::lang_nametocode(QString lang_name)
{
    QString lang_code;

    // get information about the enum named "language_list"
    QMetaObject meta_object = this->staticMetaObject;
    QMetaEnum meta_enum = meta_object.enumerator(meta_object.indexOfEnumerator("language_list"));

    //convert the language name
    switch(meta_enum.keyToValue(lang_name.toUpper().toUtf8()))
    {
        case CHINESE:
        lang_code="zh";
        break;

        case ENGLISH:
        lang_code="en";
        break;

        case FRENCH:
        lang_code="fra";
        break;

        case ITALIAN:
        lang_code="it";
        break;

        case RUSSIAN:
        lang_code="ru";
        break;

        case SPANISH:
        lang_code="spa";
        break;

        default:
        lang_code="auto";
        break;
    }

    //return language code
    return lang_code;
}

//send translation request
void MainWindow::on_translate_bt_clicked()
{
    //the api address of Baidu Translate
    QString api_addr="http://api.fanyi.baidu.com/api/trans/vip/translate?";

    //the app id registered in Baidu
    QString appid="20200218000385459";

    //get the text to be translated
    QString src_text=ui->src_text->toPlainText();

    //source language information
    QString src_lang_name=ui->src_list->currentText();
    QString src_lang_code=lang_nametocode(src_lang_name);

    //target language information
    QString tar_lang_name=ui->tar_list->currentText();
    QString tar_lang_code=lang_nametocode(tar_lang_name);

    //random code for error detecting
    //fixed value is used at here
    QString salt="1234567890";

    //the API key
    QString key="Qb1K9ELPwOAGRKrFaZ2E";

    //combine the inormation
    //appid, text, random code, api key
    QString appinfo= appid+src_text+salt+key;

    //MD5 sign of appinfo
    QString sign= md5_generate(appinfo);

    //implement the request syntax
    /*http://api.fanyi.baidu.com/api/trans/vip/translate
      ?source text
      &source language
      &app id
      &target language
      &random code
      &MD5 sign
     */
    QString address=api_addr+"q="+src_text+ "&from="+src_lang_code+"&to="+tar_lang_code
            +"&appid="+appid+"&salt="+salt+"&sign="+sign;

    //define QUrl object
    QUrl url(address.toUtf8());
    //define request object
    QNetworkRequest req(url);
    //used GET method to send request
    net_manage.get(req);

}


//this function will be automaticlly triggered with receive data from server
void MainWindow::recv_data(QNetworkReply *reply)
{
    //read the data
    QByteArray recv_msg=reply->readAll();

    //create a QJsonDocument
    QJsonDocument json_doc=QJsonDocument::fromJson(recv_msg);
    /*
    received data format：
    {"from":"zh","to":"en","trans_result":[{"src":"\u5927\u5bb6\u597d","dst":"Hello everyone"}]}

    the translation result is the value of "dst"
    */

    //parse the JSON Document
    QJsonObject json_obj= json_doc.object();

    //parse the JSON Object, create a QJsonArray
    QJsonArray trans_result_arr= json_obj.value("trans_result").toArray();

    //convert the QJsonArray to QJsonObject
    QJsonObject result_obj;
    for(int i = 0;i < trans_result_arr.size();i++)
    {
        result_obj = trans_result_arr.at(i).toObject();
    }

    //get final result from QJsonObject
    QString translation=result_obj.value("dst").toString();

    //display the result
    ui->tar_text->setText(translation);

}

//switch the source language and target language
void MainWindow::on_translate_bt_2_clicked()
{
    //get the source language name
    QString src_lang=ui->src_list->currentText();
    //get the target language name
    QString tar_lang=ui->tar_list->currentText();

    //set the text of list
    ui->tar_list->setCurrentText(src_lang);
    ui->src_list->setCurrentText(tar_lang);
}
