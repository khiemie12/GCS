#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVariant>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
union ByteToFloat{
        float myfloat;
        char mybyte[5];
    } m_data;
private slots:
        void readData();
         void fillPortAction();
         void on_btn_SetUart_clicked();
         void Setup_Grap();
         void RealTimeData();

         void on_btn_closeUart_clicked();

         void on_btn_send_clicked();

         void on_pushButton_clicked();

         void on_btn_send_2_clicked();

         void on_btn_send_4_clicked();

         void on_btn_send_9_clicked();

         void on_btn_send_10_clicked();

         void on_btn_send_11_clicked();

         void on_btn_send_12_clicked();

         void on_btn_send_13_clicked();

         void on_btn_send_3_clicked();

         void on_btn_send_5_clicked();

         void on_btn_send_6_clicked();

         void on_btn_send_7_clicked();

         void on_btn_send_8_clicked();

         void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
signals:

    void addMarker(QVariant, QVariant);
};
#endif // MAINWINDOW_H
