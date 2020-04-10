#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include <QMetaEnum>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Q_ENUMS(language_list)

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool eventFilter(QObject *watched, QEvent *event);

    //define the language list
    enum language_list
    {
        CHINESE,
        ENGLISH,
        FRENCH,
        ITALIAN,
        RUSSIAN,
        SPANISH
    };

private slots:
    void on_translate_bt_clicked();

    void recv_data(QNetworkReply *reply);

    QString md5_generate(QString src_var);

    QString lang_nametocode(QString lang_name);

    void on_translate_bt_2_clicked();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager net_manage;
};

#endif // MAINWINDOW_H
