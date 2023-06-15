#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QtDebug>
#include <QTimer>
#include <QQuickItem>
#include <qcustomplot.h>

QSerialPort SerialPort;
QTimer *timer,Uart_timer;
bool flag_PlotTimer;

static float Roll_Angle;
static  short Pitch_Angle;
static float Yaw_Angle;

static float Roll_SetPoint;
static float Pitch_SetPoint;
static float Yaw_SetPoint;

static float Roll_Inner_P;
static float Roll_Inner_I;
static float Roll_Inner_D;

static float Pitch_Inner_P;
static float Pitch_Inner_I;
static float Pitch_Inner_D;

static float Roll_Outer_P;
static float Roll_Outer_I;
static float Roll_Outer_D;

static float Pitch_Outer_P;
static float Pitch_Outer_I;
static float Pitch_Outer_D;

static float Yaw_heading_P;
static float Yaw_heading_I;
static float Yaw_heading_D;

static float Yaw_rate_P;
static float Yaw_rate_I;
static float Yaw_rate_D;

static float Roll_Inner_P_request;
static float Roll_Inner_I_request;
static float Roll_Inner_D_request;

static float Pitch_Inner_P_request;
static float Pitch_Inner_I_request;
static float Pitch_Inner_D_request;

static float Roll_Outer_P_request;
static float Roll_Outer_I_request;
static float Roll_Outer_D_request;

static float Pitch_Outer_P_request;
static float Pitch_Outer_I_request;
static float Pitch_Outer_D_request;

static float Yaw_heading_P_request;
static float Yaw_heading_I_request;
static float Yaw_heading_D_request;


static float Yaw_rate_P_request;
static float Yaw_rate_I_request;
static float Yaw_rate_D_request;

static unsigned short battery_voltage;
static float swA;
static float swC;
static float fail_safe;
static long GPS_Longtitude;
static long  GPS_Lattitude;

static unsigned short Altitude;
 short transfer;

int checksum;


int c=0;


char rxbuff[20];



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Setup_Grap();
    Uart_timer.setInterval(1000);


    connect(&Uart_timer,SIGNAL(timeout()),this,SLOT(readData()));
    fillPortAction();

    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
      ui->quickWidget->show();

      auto obj = ui->quickWidget->rootObject();

      connect(this, SIGNAL(addMarker(QVariant, QVariant)), obj, SLOT(addMarker(QVariant, QVariant)));

//      emit setCenter(25.000, 50.000);
      emit addMarker(25.000, 50.000);
}
void MainWindow::readData()
{

        QByteArray read_buffer = SerialPort.readAll();

        QByteArray byte_data;


                                          if(!read_buffer.isEmpty()){
                                    byte_data.append(read_buffer);

                                     c=0;



                                    if (byte_data.length()>=40){


if(byte_data.startsWith("FC")){
                                qDebug()<<byte_data;

                                 checksum=0xFF;

//                                 for(int i=c;i<(c+19);i++) checksum = checksum - byte_data[i];

//                                 if(checksum==byte_data[c+19])
//                                 {


                               switch(byte_data[c+2])
                               {
                               case 0x00:

                                   rxbuff[3]=byte_data[c+3];
                                   rxbuff[4]=byte_data[c+4];
                                   rxbuff[5]=byte_data[c+5];
                                   rxbuff[6]=byte_data[c+6];
                                   rxbuff[7]=byte_data[c+7];
                                   rxbuff[8]=byte_data[c+8];
                                   rxbuff[9]=byte_data[c+9];
                                   rxbuff[10]=byte_data[c+10];
                                   rxbuff[11]=byte_data[c+11];
                                   rxbuff[12]=byte_data[c+12];
                                   rxbuff[13]=byte_data[c+13];
                                   rxbuff[14]=byte_data[c+14];
                                   Roll_Inner_P_request=*(float*)&rxbuff[3];
                                   Roll_Inner_I_request=*(float*)&rxbuff[7];
                                   Roll_Inner_D_request=*(float*)&rxbuff[11];
                                   ui->lineEdit_25->setText(QString::number(Roll_Inner_P_request, 'f', 3));
                                   ui->lineEdit_30->setText(QString::number(Roll_Inner_I_request, 'f', 3));
                                   ui->lineEdit_33->setText(QString::number(Roll_Inner_D_request, 'f', 3));


                                   break;


                               case 0x01:


                                   rxbuff[3]=byte_data[c+3];
                                   rxbuff[4]=byte_data[c+4];
                                   rxbuff[5]=byte_data[c+5];
                                   rxbuff[6]=byte_data[c+6];
                                   rxbuff[7]=byte_data[c+7];
                                   rxbuff[8]=byte_data[c+8];
                                   rxbuff[9]=byte_data[c+9];
                                   rxbuff[10]=byte_data[c+10];
                                   rxbuff[11]=byte_data[c+11];
                                   rxbuff[12]=byte_data[c+12];
                                   rxbuff[13]=byte_data[c+13];
                                   rxbuff[14]=byte_data[c+14];
                                   Roll_Outer_P_request=*(float*)&rxbuff[3];
                                   Roll_Outer_I_request=*(float*)&rxbuff[7];
                                   Roll_Outer_D_request=*(float*)&rxbuff[11];
                                   ui->lineEdit_19->setText(QString::number(Roll_Outer_P_request, 'f', 3));
                                   ui->lineEdit_24->setText(QString::number(Roll_Outer_I_request, 'f', 3));
                                   ui->lineEdit_23->setText(QString::number( Roll_Outer_D_request, 'f', 3));



                                   break;

                               case 0x02:
                                   rxbuff[3]=byte_data[c+3];
                                   rxbuff[4]=byte_data[c+4];
                                   rxbuff[5]=byte_data[c+5];
                                   rxbuff[6]=byte_data[c+6];
                                   rxbuff[7]=byte_data[c+7];
                                   rxbuff[8]=byte_data[c+8];
                                   rxbuff[9]=byte_data[c+9];
                                   rxbuff[10]=byte_data[c+10];
                                   rxbuff[11]=byte_data[c+11];
                                   rxbuff[12]=byte_data[c+12];
                                   rxbuff[13]=byte_data[c+13];
                                   rxbuff[14]=byte_data[c+14];
                                   Pitch_Inner_P_request=*(float*)&rxbuff[3];
                                   Pitch_Inner_I_request=*(float*)&rxbuff[7];
                                   Pitch_Inner_D_request=*(float*)&rxbuff[11];

                                   ui->lineEdit_27->setText(QString::number(Pitch_Inner_P_request, 'f', 3));
                                   ui->lineEdit_20->setText(QString::number( Pitch_Inner_I_request, 'f', 3));
                                   ui->lineEdit_31->setText(QString::number(Pitch_Inner_D_request, 'f', 3));

                                   break;

                               case 0x03:
                                   rxbuff[3]=byte_data[c+3];
                                   rxbuff[4]=byte_data[c+4];
                                   rxbuff[5]=byte_data[c+5];
                                   rxbuff[6]=byte_data[c+6];
                                   rxbuff[7]=byte_data[c+7];
                                   rxbuff[8]=byte_data[c+8];
                                   rxbuff[9]=byte_data[c+9];
                                   rxbuff[10]=byte_data[c+10];
                                   rxbuff[11]=byte_data[c+11];
                                   rxbuff[12]=byte_data[c+12];
                                   rxbuff[13]=byte_data[c+13];
                                   rxbuff[14]=byte_data[c+14];
                                   Pitch_Outer_P_request=*(float*)&rxbuff[3];
                                   Pitch_Outer_I_request=*(float*)&rxbuff[7];
                                   Pitch_Outer_D_request=*(float*)&rxbuff[11];


                                   ui->lineEdit_21->setText(QString::number( Pitch_Outer_P_request, 'f', 3));
                                   ui->lineEdit_28->setText(QString::number(Pitch_Outer_I_request, 'f', 3));
                                   ui->lineEdit_35->setText(QString::number(Pitch_Outer_D_request, 'f', 3));
                                   break;

                               case 0x04:
                                   rxbuff[3]=byte_data[c+3];
                                   rxbuff[4]=byte_data[c+4];
                                   rxbuff[5]=byte_data[c+5];
                                   rxbuff[6]=byte_data[c+6];
                                   rxbuff[7]=byte_data[c+7];
                                   rxbuff[8]=byte_data[c+8];
                                   rxbuff[9]=byte_data[c+9];
                                   rxbuff[10]=byte_data[c+10];
                                   rxbuff[11]=byte_data[c+11];
                                   rxbuff[12]=byte_data[c+12];
                                   rxbuff[13]=byte_data[c+13];
                                   rxbuff[14]=byte_data[c+14];
                                   Yaw_heading_P_request=*(float*)&rxbuff[3];
                                   Yaw_heading_I_request=*(float*)&rxbuff[7];
                                   Yaw_heading_D_request=*(float*)&rxbuff[11];

                                  ui->lineEdit_36->setText(QString::number(Yaw_heading_P_request, 'f', 3));
                                  ui->lineEdit_22->setText(QString::number(Yaw_heading_I_request, 'f', 3));
                                  ui->lineEdit_34->setText(QString::number(Yaw_heading_D_request, 'f', 3));

                                   break;

                               case 0x05:
                                   rxbuff[3]=byte_data[c+3];
                                   rxbuff[4]=byte_data[c+4];
                                   rxbuff[5]=byte_data[c+5];
                                   rxbuff[6]=byte_data[c+6];
                                   rxbuff[7]=byte_data[c+7];
                                   rxbuff[8]=byte_data[c+8];
                                   rxbuff[9]=byte_data[c+9];
                                   rxbuff[10]=byte_data[c+10];
                                   rxbuff[11]=byte_data[c+11];
                                   rxbuff[12]=byte_data[c+12];
                                   rxbuff[13]=byte_data[c+13];
                                   rxbuff[14]=byte_data[c+14];
                                   Yaw_rate_P_request=*(float*)&rxbuff[3];
                                   Yaw_rate_I_request=*(float*)&rxbuff[7];
                                   Yaw_rate_D_request=*(float*)&rxbuff[11];
                                   ui->lineEdit_29->setText(QString::number(Yaw_rate_P_request, 'f', 3));
                                   ui->lineEdit_26->setText(QString::number(Yaw_rate_I_request, 'f', 3));
                                   ui->lineEdit_32->setText(QString::number(Yaw_rate_D_request, 'f', 3));
                                   break;

                               case 0x10:
                                   rxbuff[3]=byte_data[c+3];
                                   rxbuff[4]=byte_data[c+4];
                                   rxbuff[5]=byte_data[c+5];
                                   rxbuff[6]=byte_data[c+6];
                                   rxbuff[7]=byte_data[c+7];
                                   rxbuff[8]=byte_data[c+8];
                                   rxbuff[9]=byte_data[c+9];
                                   rxbuff[10]=byte_data[c+10];
                                   rxbuff[11]=byte_data[c+11];
                                   rxbuff[12]=byte_data[c+12];
                                   rxbuff[13]=byte_data[c+13];
                                   rxbuff[14]=byte_data[c+14];
//                                    static float pitch;
                                  Roll_Angle = (short) (((byte_data[c+3]) | (byte_data[c+4]<<8)) * 0.01);
//                                  Pitch_Angle = (short) ((byte_data[c+5]) | (byte_data[c+6]<<8)) * 0.01;
                                  Yaw_Angle = (short) ((byte_data[c+7]) | (byte_data[c+8]<<8)) * 0.01;
//                                  Pitch_Angle =(unsigned short) ( byte_data[c+5]<<8 | (byte_data[c+6]));
//                                  transfer=byte_data[c+5];
//                                  if(transfer<0){
//                                  Pitch_Angle= Pitch_Angle & 0x00ff;
//                                 Pitch_Angle = Pitch_Angle | byte_data[c+6]<<8 ;

//                                  }
//                                  pitch=(Pitch_Angle)*0.01f-100;

//                                  Altitude =(unsigned short) ( byte_data[c+10]<<8 | (byte_data[c+9]));
//                                  transfer=byte_data[c+9];
//                                  if(transfer<0){
//                                  Altitude= Altitude & 0x00ff;
//                                  Altitude = Altitude | byte_data[c+10]<<8 ;

//                                  }
                                  Altitude=*(unsigned short*)&rxbuff[9];

                                  Pitch_Angle=*(short*)&rxbuff[5];
                                  Pitch_Angle=Pitch_Angle*0.01-100;
                                    Pitch_SetPoint=*(short*)&rxbuff[13];
                                    Pitch_SetPoint=Pitch_SetPoint*0.01-97.4;
                                  Roll_SetPoint = (short) ((byte_data[c+11]) | (byte_data[c+12]<<8)) * 0.01;
//                                  Pitch_SetPoint = (short) ((byte_data[c+13]) | (byte_data[c+14]<<8))* 0.01;
                                  Yaw_SetPoint = (short) ((byte_data[c+15]) | (byte_data[c+16]<<8))* 0.01;
                                  ui->lcdNumber_43->display(Roll_Angle);
                                  ui->lcdNumber_44->display( Pitch_Angle);
                                  ui->lcdNumber_45->display(Yaw_Angle);
                                  ui->lcdNumber_46->display(Roll_SetPoint);
                                  ui->lcdNumber_47->display(Pitch_SetPoint);
                                  ui->lcdNumber_48->display(Yaw_SetPoint);
                                  ui->lcdNumber->display(Altitude*0.1f);

                                   break;

                               case 0x11:
                                   rxbuff[3]=byte_data[c+3];
                                   rxbuff[4]=byte_data[c+4];
                                   rxbuff[5]=byte_data[c+5];
                                   rxbuff[6]=byte_data[c+6];
                                   rxbuff[7]=byte_data[c+7];
                                   rxbuff[8]=byte_data[c+8];
                                   rxbuff[9]=byte_data[c+9];
                                   rxbuff[10]=byte_data[c+10];
                                   GPS_Lattitude=*(long*)&rxbuff[3];
                                   GPS_Longtitude=*(long*)&rxbuff[7];


                                    battery_voltage =(unsigned short) ( byte_data[12]<<8 | (byte_data[11]));
                                   transfer=byte_data[11];
                                   if(transfer<0){
                                    battery_voltage=  battery_voltage & 0x00ff;
                                   battery_voltage = battery_voltage | byte_data[12]<<8 ;

                                   }



                                   swA = byte_data[c+13];
                                   swC = byte_data[c+14];
                                   fail_safe = byte_data[c+15];
//                                   GPS_Lattitude =(unsigned int) ((byte_data[c+3]) | (byte_data[c+4]<<8) | (byte_data[c+5]<<16) | (byte_data[c+6]<<24))  ;
//                                   GPS_Longtitude =(unsigned int) ((byte_data[c+7]) | (byte_data[c+8]<<8) | (byte_data[c+9]<<16) | (byte_data[c+10]<<24)) ;
                                   ui->lcdNumber_4->display(swA);
                                   ui->lcdNumber_5->display(swC);
                                                                     ui->lcdNumber_2->display(QString::number(GPS_Lattitude));
                                                                     ui->lcdNumber_8->display(QString::number(GPS_Longtitude));
                                                                     ui->lcdNumber_3->display(battery_voltage*0.01f);

                                                                     ui->lcdNumber_6->display(fail_safe);
                                                                     break;


//                                  }

                                 }
}


if(byte_data[c+20]=='F'&&byte_data[c+21]=='C'){
   c=c+20;
   checksum=0xFF;

//   for(int i=c;i<(c+19);i++) checksum = checksum - byte_data[i];

//   if(checksum==byte_data[c+19])
//   {

    switch(byte_data[c+2])
    {
    case 0x00:

        rxbuff[3]=byte_data[c+3];
        rxbuff[4]=byte_data[c+4];
        rxbuff[5]=byte_data[c+5];
        rxbuff[6]=byte_data[c+6];
        rxbuff[7]=byte_data[c+7];
        rxbuff[8]=byte_data[c+8];
        rxbuff[9]=byte_data[c+9];
        rxbuff[10]=byte_data[c+10];
        rxbuff[11]=byte_data[c+11];
        rxbuff[12]=byte_data[c+12];
        rxbuff[13]=byte_data[c+13];
        rxbuff[14]=byte_data[c+14];
        Roll_Inner_P_request=*(float*)&rxbuff[3];
        Roll_Inner_I_request=*(float*)&rxbuff[7];
        Roll_Inner_D_request=*(float*)&rxbuff[11];
        ui->lineEdit_25->setText(QString::number(Roll_Inner_P_request, 'f', 3));
        ui->lineEdit_30->setText(QString::number(Roll_Inner_I_request, 'f', 3));
        ui->lineEdit_33->setText(QString::number(Roll_Inner_D_request, 'f', 3));

        break;


    case 0x01:


                                           rxbuff[3]=byte_data[c+3];
                                           rxbuff[4]=byte_data[c+4];
                                           rxbuff[5]=byte_data[c+5];
                                           rxbuff[6]=byte_data[c+6];
                                           rxbuff[7]=byte_data[c+7];
                                           rxbuff[8]=byte_data[c+8];
                                           rxbuff[9]=byte_data[c+9];
                                           rxbuff[10]=byte_data[c+10];
                                           rxbuff[11]=byte_data[c+11];
                                           rxbuff[12]=byte_data[c+12];
                                           rxbuff[13]=byte_data[c+13];
                                           rxbuff[14]=byte_data[c+14];
                                           Roll_Outer_P_request=*(float*)&rxbuff[3];
                                           Roll_Outer_I_request=*(float*)&rxbuff[7];
                                           Roll_Outer_D_request=*(float*)&rxbuff[11];
                                           ui->lineEdit_19->setText(QString::number(Roll_Outer_P_request, 'f', 3));
                                           ui->lineEdit_24->setText(QString::number(Roll_Outer_I_request, 'f', 3));
                                           ui->lineEdit_23->setText(QString::number( Roll_Outer_D_request, 'f', 3));


break;
    case 0x02:

        rxbuff[3]=byte_data[c+3];
        rxbuff[4]=byte_data[c+4];
        rxbuff[5]=byte_data[c+5];
        rxbuff[6]=byte_data[c+6];
        rxbuff[7]=byte_data[c+7];
        rxbuff[8]=byte_data[c+8];
        rxbuff[9]=byte_data[c+9];
        rxbuff[10]=byte_data[c+10];
        rxbuff[11]=byte_data[c+11];
        rxbuff[12]=byte_data[c+12];
        rxbuff[13]=byte_data[c+13];
        rxbuff[14]=byte_data[c+14];
        Pitch_Inner_P_request=*(float*)&rxbuff[3];
        Pitch_Inner_I_request=*(float*)&rxbuff[7];
        Pitch_Inner_D_request=*(float*)&rxbuff[11];

        ui->lineEdit_27->setText(QString::number(Pitch_Inner_P_request, 'f', 3));
        ui->lineEdit_20->setText(QString::number( Pitch_Inner_I_request, 'f', 3));
        ui->lineEdit_31->setText(QString::number(Pitch_Inner_D_request, 'f', 3));

        break;

    case 0x03:

        rxbuff[3]=byte_data[c+3];
        rxbuff[4]=byte_data[c+4];
        rxbuff[5]=byte_data[c+5];
        rxbuff[6]=byte_data[c+6];
        rxbuff[7]=byte_data[c+7];
        rxbuff[8]=byte_data[c+8];
        rxbuff[9]=byte_data[c+9];
        rxbuff[10]=byte_data[c+10];
        rxbuff[11]=byte_data[c+11];
        rxbuff[12]=byte_data[c+12];
        rxbuff[13]=byte_data[c+13];
        rxbuff[14]=byte_data[c+14];
        Pitch_Outer_P_request=*(float*)&rxbuff[3];
        Pitch_Outer_I_request=*(float*)&rxbuff[7];
        Pitch_Outer_D_request=*(float*)&rxbuff[11];


        ui->lineEdit_21->setText(QString::number( Pitch_Outer_P_request, 'f', 3));
        ui->lineEdit_28->setText(QString::number(Pitch_Outer_I_request, 'f', 3));
        ui->lineEdit_35->setText(QString::number(Pitch_Outer_D_request, 'f', 3));
        break;



    case 0x04:

        rxbuff[3]=byte_data[c+3];
        rxbuff[4]=byte_data[c+4];
        rxbuff[5]=byte_data[c+5];
        rxbuff[6]=byte_data[c+6];
        rxbuff[7]=byte_data[c+7];
        rxbuff[8]=byte_data[c+8];
        rxbuff[9]=byte_data[c+9];
        rxbuff[10]=byte_data[c+10];
        rxbuff[11]=byte_data[c+11];
        rxbuff[12]=byte_data[c+12];
        rxbuff[13]=byte_data[c+13];
        rxbuff[14]=byte_data[c+14];
        Yaw_heading_P_request=*(float*)&rxbuff[3];
        Yaw_heading_I_request=*(float*)&rxbuff[7];
        Yaw_heading_D_request=*(float*)&rxbuff[11];


       ui->lineEdit_36->setText(QString::number(Yaw_heading_P_request, 'f', 3));
       ui->lineEdit_22->setText(QString::number(Yaw_heading_I_request, 'f', 3));
       ui->lineEdit_34->setText(QString::number(Yaw_heading_D_request, 'f', 3));

        break;

    case 0x05:

        rxbuff[3]=byte_data[c+3];
        rxbuff[4]=byte_data[c+4];
        rxbuff[5]=byte_data[c+5];
        rxbuff[6]=byte_data[c+6];
        rxbuff[7]=byte_data[c+7];
        rxbuff[8]=byte_data[c+8];
        rxbuff[9]=byte_data[c+9];
        rxbuff[10]=byte_data[c+10];
        rxbuff[11]=byte_data[c+11];
        rxbuff[12]=byte_data[c+12];
        rxbuff[13]=byte_data[c+13];
        rxbuff[14]=byte_data[c+14];

        Yaw_rate_P_request=*(float*)&rxbuff[3];
        Yaw_rate_I_request=*(float*)&rxbuff[7];
        Yaw_rate_D_request=*(float*)&rxbuff[11];
        ui->lineEdit_29->setText(QString::number(Yaw_rate_P_request, 'f', 3));
        ui->lineEdit_26->setText(QString::number(Yaw_rate_I_request, 'f', 3));
        ui->lineEdit_32->setText(QString::number(Yaw_rate_D_request, 'f', 3));
        break;

    case 0x10:
        rxbuff[3]=byte_data[c+3];
        rxbuff[4]=byte_data[c+4];
        rxbuff[5]=byte_data[c+5];
        rxbuff[6]=byte_data[c+6];
        rxbuff[7]=byte_data[c+7];
        rxbuff[8]=byte_data[c+8];
        rxbuff[9]=byte_data[c+9];
        rxbuff[10]=byte_data[c+10];
        rxbuff[11]=byte_data[c+11];
        rxbuff[12]=byte_data[c+12];
        rxbuff[13]=byte_data[c+13];
        rxbuff[14]=byte_data[c+14];
//        static float pitch;
       Roll_Angle = (short) (((byte_data[c+3]) | (byte_data[c+4]<<8)) * 0.01);
//       Pitch_Angle = (short) ((byte_data[c+5]) | (byte_data[c+6]<<8)) * 0.01;
       Yaw_Angle = (short) ((byte_data[c+7]) | (byte_data[c+8]<<8)) * 0.01;


//       Pitch_Angle =(unsigned short) ( byte_data[c+5]<<8 | (byte_data[c+6]));
//       transfer=byte_data[c+5];
//       if(transfer<0){
//       Pitch_Angle= Pitch_Angle & 0x00ff;
//      Pitch_Angle = Pitch_Angle | byte_data[c+6]<<8 ;

//       }
//       pitch=(Pitch_Angle)*0.01-100;

//       Altitude =(unsigned short) ( byte_data[c+10]<<8 | (byte_data[c+9]));
//       transfer=byte_data[c+9];
//       if(transfer<0){
//       Altitude= Altitude & 0x00ff;
//       Altitude = Altitude | byte_data[c+10]<<8 ;

//       }
       Altitude=*(unsigned short*)&rxbuff[9];

        Pitch_Angle=*(short*)&rxbuff[5];
        Pitch_Angle=Pitch_Angle*0.01-100;
        Pitch_SetPoint=*(short*)&rxbuff[13];
        Pitch_SetPoint=Pitch_SetPoint*0.01-97.4;


       Roll_SetPoint = (short) ((byte_data[c+11]) | (byte_data[c+12]<<8)) * 0.01;
//       Pitch_SetPoint = (short) ((byte_data[c+13]) | (byte_data[c+14]<<8))* 0.01;
       Yaw_SetPoint = (short) ((byte_data[c+15]) | (byte_data[c+16]<<8))* 0.01;
       ui->lcdNumber_43->display(Roll_Angle);
       ui->lcdNumber_44->display(Pitch_Angle);
       ui->lcdNumber_45->display(Yaw_Angle);
       ui->lcdNumber_46->display(Roll_SetPoint);
       ui->lcdNumber_47->display(Pitch_SetPoint);
       ui->lcdNumber_48->display(Yaw_SetPoint);
       ui->lcdNumber->display(Altitude*0.1f);

        break;

    case 0x11:
        rxbuff[3]=byte_data[c+3];
        rxbuff[4]=byte_data[c+4];
        rxbuff[5]=byte_data[c+5];
        rxbuff[6]=byte_data[c+6];
        rxbuff[7]=byte_data[c+7];
        rxbuff[8]=byte_data[c+8];
        rxbuff[9]=byte_data[c+9];
        rxbuff[10]=byte_data[c+10];
        GPS_Lattitude=*(long*)&rxbuff[3];
        GPS_Longtitude=*(long*)&rxbuff[7];

         battery_voltage =(unsigned short) ( byte_data[c+12]<<8 | (byte_data[c+11]));
        transfer=byte_data[c+11];
        if(transfer<0){
         battery_voltage=  battery_voltage & 0x00ff;
        battery_voltage = battery_voltage | byte_data[c+12]<<8 ;

        }



        swA = byte_data[c+13];
        swC = byte_data[c+14];
        fail_safe = byte_data[c+15];
//        GPS_Lattitude =(int) ((byte_data[c+3]) | (byte_data[c+4]<<8) | (byte_data[c+5]<<16) | (byte_data[c+6]<<24))  ;
//        GPS_Longtitude =(int) ((byte_data[c+7]) | (byte_data[c+8]<<8) | (byte_data[c+9]<<16) | (byte_data[c+10]<<24)) ;
        ui->lcdNumber_4->display(swA);
        ui->lcdNumber_5->display(swC);
        ui->lcdNumber_2->display(QString::number(GPS_Lattitude));
        ui->lcdNumber_8->display(QString::number(GPS_Longtitude));
        ui->lcdNumber_3->display(battery_voltage*0.01f);

        ui->lcdNumber_6->display(fail_safe);
        break;


        }


}
}


byte_data.remove(0,40);


                                    }
                                          RealTimeData();

}
void MainWindow::RealTimeData(){

    static double yMax=0;
    static double temp_time=0;
    static QTime time(QTime::currentTime());

    double key = time.elapsed()/1000.0;
    ui->customplot->graph(0)->addData(key, Pitch_Angle);
    ui->customplot->graph(1)->addData(key, Pitch_SetPoint);
    ui->customplot->graph(0)->rescaleValueAxis();
    ui->customplot->xAxis->setRange(temp_time, key, Qt::AlignLeft);
    if(Pitch_SetPoint >= yMax) yMax= Pitch_SetPoint;
    if(Pitch_Angle >= yMax) yMax = Pitch_Angle;
    ui->customplot->yAxis->setRange(-39,yMax+20);
    ui->customplot->replot();
    // calculate frames per second:
    static double lastFpsKey;
    static int frameCount;
    ++frameCount;
    lastFpsKey = key;
    frameCount = 0;

}
void MainWindow::Setup_Grap()
{
 ui->customplot->addGraph(); // blue line
 ui->customplot->graph(0)->setPen(QPen(QColor(40, 110, 255)));
 ui->customplot->addGraph(); // red line
 ui->customplot->graph(1)->setPen(QPen(QColor(255, 110, 40)));
 QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
 timeTicker->setTimeFormat("%h:%m:%s");
 ui->customplot->xAxis->setTicker(timeTicker);
 ui->customplot->axisRect()->setupFullAxesBox();
 ui->customplot->yAxis->setRange(-100,100);
 // make left and bottom axes transfer their ranges to right and top axes:
 connect(ui->customplot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customplot->xAxis2, SLOT(setRange(QCPRange)));
 connect(ui->customplot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customplot->yAxis2, SLOT(setRange(QCPRange)));
 // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
// connect(&Uart_timer, SIGNAL(timeout()), this, SLOT(RealTimeData()));
// Uart_timer.start(0);
}
void MainWindow::fillPortAction()
{
    const auto infos = QSerialPortInfo::availablePorts();
    for(const QSerialPortInfo &info : infos)
    {
        ui->ComUart->addItem(info.portName());  //ham dung de tao option
    }
    ui->baudRateBox->addItem(QStringLiteral("9600"), QSerialPort::Baud9600);
    ui->baudRateBox->addItem(QStringLiteral("19200"),QSerialPort::Baud19200);
    ui->baudRateBox->addItem(QStringLiteral("38400"),QSerialPort::Baud38400);
    ui->baudRateBox->addItem(QStringLiteral("57600"),QSerialPort::Baud57600);
    ui->baudRateBox->addItem(QStringLiteral("115200"),QSerialPort::Baud115200);
    ui->baudRateBox->addItem(tr("Custom"));

    ui->dataBitsBox->addItem(QStringLiteral("5"), QSerialPort::Data5);
    ui->dataBitsBox->addItem(QStringLiteral("6"), QSerialPort::Data6);
    ui->dataBitsBox->addItem(QStringLiteral("7"), QSerialPort::Data7);
    ui->dataBitsBox->addItem(QStringLiteral("8"), QSerialPort::Data8);
    //ui->dataBitsBox->hide();
    ui->dataBitsBox->setCurrentIndex(3);

    ui->parityBox->addItem(tr("None"), QSerialPort::NoParity);
    //ui->parityBox->hide();
    ui->parityBox->addItem(tr("Even"), QSerialPort::EvenParity);
    ui->parityBox->addItem(tr("Odd"), QSerialPort::OddParity);
    ui->parityBox->addItem(tr("Mark"), QSerialPort::MarkParity);
    ui->parityBox->addItem(tr("Space"), QSerialPort::SpaceParity);


    ui->stopBitsBox->addItem(QStringLiteral("1"), QSerialPort::OneStop);
   // ui->stopBitsBox->hide();
    ui->stopBitsBox->addItem(QStringLiteral("2"), QSerialPort::TwoStop);

    ui->flowControlBox->addItem(tr("None"), QSerialPort::NoFlowControl);
    //ui->flowControlBox->hide();
    ui->flowControlBox->addItem(tr("RTS/CTS"),QSerialPort::HardwareControl);
    ui->flowControlBox->addItem(tr("XON/XOFF"),QSerialPort::SoftwareControl);
}
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_SetUart_clicked()
{
    SerialPort.setPortName(ui->ComUart->currentText());
    SerialPort.setBaudRate(ui->baudRateBox->currentText().toInt());
    SerialPort.setDataBits(static_cast<QSerialPort::DataBits>(
    ui->dataBitsBox->itemData(ui->dataBitsBox->currentIndex()).toInt()));
    SerialPort.setParity(static_cast<QSerialPort::Parity>(ui->parityBox->itemData(ui->parityBox->currentIndex()).toInt()));
    SerialPort.setStopBits(static_cast<QSerialPort::StopBits>(
    ui->stopBitsBox->itemData(ui->stopBitsBox->currentIndex()).toInt()));
    SerialPort.setFlowControl(static_cast<QSerialPort::FlowControl>(
    ui->flowControlBox->itemData(ui->flowControlBox->currentIndex()).toInt()));
    SerialPort.open(QIODevice::ReadWrite);
    //connect(SerialPort, &QSerialPort::readyRead, this,&MainWindow::readData);
    Uart_timer.start(40);
    // Interval 0 means to refresh as fast as possible
}


void MainWindow::on_btn_closeUart_clicked()
{
        SerialPort.close();
}


void MainWindow::on_btn_send_clicked()
{
    QByteArray txbuff;
    uint8_t telemetry_tx_buf[20];
        QString text_Roll_inner_P;
        QString text_Roll_inner_I;
        QString text_Roll_inner_D;
        bool ok;
        int flag=1;

        text_Roll_inner_P= ui->lineEdit->displayText();
        Roll_Inner_P=text_Roll_inner_P.toFloat(&ok);
        if(!ok)
        {
            ui->lineEdit->setText("Invalid value");
            flag=0;
        }

        text_Roll_inner_I= ui->lineEdit_2->displayText();
        Roll_Inner_I=text_Roll_inner_I.toFloat(&ok);
        if(!ok)
        {
            ui->lineEdit_2->setText("Invalid value");
            flag=0;
        }

        text_Roll_inner_D= ui->lineEdit_3->displayText();
        Roll_Inner_D=text_Roll_inner_D.toFloat(&ok);
        if(!ok)
        {
            ui->lineEdit_3->setText("Invalid value");
            flag=0;
        }

        if(flag == 1)
        {

                 txbuff[0] = 0x47;
                 txbuff[1] = 0x53;
                 txbuff[2] = 0x00;

                 *(float*)&telemetry_tx_buf[3] = Roll_Inner_P ;
                 *(float*)&telemetry_tx_buf[7] = Roll_Inner_I;
                 *(float*)&telemetry_tx_buf[11] = Roll_Inner_D;

                 txbuff[3] = telemetry_tx_buf[3];
                 txbuff[4] = telemetry_tx_buf[4];
                 txbuff[5] = telemetry_tx_buf[5];
                 txbuff[6] = telemetry_tx_buf[6];
                 txbuff[7] = telemetry_tx_buf[7];
                 txbuff[8] = telemetry_tx_buf[8];
                 txbuff[9] = telemetry_tx_buf[9];
                 txbuff[10] = telemetry_tx_buf[10];
                 txbuff[11] = telemetry_tx_buf[11];
                 txbuff[12] = telemetry_tx_buf[12];
                 txbuff[13] = telemetry_tx_buf[13];
                 txbuff[14] = telemetry_tx_buf[14];
                 txbuff[15] = 0x00;
                 txbuff[16] = 0x00;
                 txbuff[17] = 0x00;
                 txbuff[18] = 0x00;

                 txbuff[19] = 0xff;

                 for(int i=0;i<19;i++) txbuff[19] = txbuff[19] - txbuff[i];

            SerialPort.write(txbuff,20);




        }

}


void MainWindow::on_pushButton_clicked()
{
    QByteArray txbuff;
    txbuff[0] = 0x47;
    txbuff[1] = 0x53;
    txbuff[2] = 0x10;
    txbuff[3] = 0x07;
    txbuff[4] = 0x01;
    txbuff[5] = 0x00;
    txbuff[6] = 0x00;
    txbuff[7] = 0x00;
    txbuff[8] = 0x00;
    txbuff[9] = 0x00;
    txbuff[10] = 0x00;
    txbuff[11] = 0x00;
    txbuff[12] = 0x00;
    txbuff[13] = 0x00;
    txbuff[14] = 0x00;
    txbuff[15] = 0x00;
    txbuff[16] = 0x00;
    txbuff[17] = 0x00;
    txbuff[18] = 0x00;
    txbuff[19] = 0xff;
    for(int i=0;i<19;i++) txbuff[19] = txbuff[19] - txbuff[i];
    SerialPort.write(txbuff,20);


}



void MainWindow::on_btn_send_2_clicked()
{
    QByteArray txbuff;
    txbuff[0] = 0x47;
    txbuff[1] = 0x53;
    txbuff[2] = 0x10;
    txbuff[3] = 0x00;
    txbuff[4] = 0x00;
    txbuff[5] = 0x00;
    txbuff[6] = 0x00;
    txbuff[7] = 0x00;
    txbuff[8] = 0x00;
    txbuff[9] = 0x00;
    txbuff[10] = 0x00;
    txbuff[11] = 0x00;
    txbuff[12] = 0x00;
    txbuff[13] = 0x00;
    txbuff[14] = 0x00;
    txbuff[15] = 0x00;
    txbuff[16] = 0x00;
    txbuff[17] = 0x00;
    txbuff[18] = 0x00;
    txbuff[19] = 0xff;

    for(int i=0;i<19;i++) txbuff[19] = txbuff[19] - txbuff[i];
    SerialPort.write(txbuff,20);



}



void MainWindow::on_btn_send_4_clicked()
{
    ui->lineEdit->setText(QString::number(Roll_Inner_P));
    ui->lineEdit_2->setText(QString::number(Roll_Inner_I));
    ui->lineEdit_3->setText(QString::number(Roll_Inner_D));

    ui->lineEdit_7->setText(QString::number(Roll_Outer_P));
    ui->lineEdit_8->setText(QString::number(Roll_Outer_I));
    ui->lineEdit_9->setText(QString::number(Roll_Outer_D));

    ui->lineEdit_4->setText(QString::number(Pitch_Inner_P));
    ui->lineEdit_5->setText(QString::number(Pitch_Inner_I));
    ui->lineEdit_6->setText(QString::number(Pitch_Inner_D));

    ui->lineEdit_10->setText(QString::number(Pitch_Outer_P));
    ui->lineEdit_11->setText(QString::number(Pitch_Outer_I));
    ui->lineEdit_12->setText(QString::number(Pitch_Outer_D));

    ui->lineEdit_13->setText(QString::number(Yaw_heading_P));
    ui->lineEdit_14->setText(QString::number(Yaw_heading_I));
    ui->lineEdit_15->setText(QString::number(Yaw_heading_D));

    ui->lineEdit_16->setText(QString::number(Yaw_rate_P));
    ui->lineEdit_17->setText(QString::number(Yaw_rate_I));
    ui->lineEdit_18->setText(QString::number(Yaw_rate_D));
}


void MainWindow::on_btn_send_9_clicked()
{
    QByteArray txbuff;
    txbuff[0] = 0x47;
    txbuff[1] = 0x53;
    txbuff[2] = 0x10;
    txbuff[3] = 0x02;
    txbuff[4] = 0x00;
    txbuff[5] = 0x00;
    txbuff[6] = 0x00;
    txbuff[7] = 0x00;
    txbuff[8] = 0x00;
    txbuff[9] = 0x00;
    txbuff[10] = 0x00;
    txbuff[11] = 0x00;
    txbuff[12] = 0x00;
    txbuff[13] = 0x00;
    txbuff[14] = 0x00;
    txbuff[15] = 0x00;
    txbuff[16] = 0x00;
    txbuff[17] = 0x00;
    txbuff[18] = 0x00;
    txbuff[19] = 0xff;

    for(int i=0;i<19;i++) txbuff[19] = txbuff[19] - txbuff[i];
    SerialPort.write(txbuff,20);

}


void MainWindow::on_btn_send_10_clicked()
{
    QByteArray txbuff;
    txbuff[0] = 0x47;
    txbuff[1] = 0x53;
    txbuff[2] = 0x10;
    txbuff[3] = 0x01;
    txbuff[4] = 0x00;
    txbuff[5] = 0x00;
    txbuff[6] = 0x00;
    txbuff[7] = 0x00;
    txbuff[8] = 0x00;
    txbuff[9] = 0x00;
    txbuff[10] = 0x00;
    txbuff[11] = 0x00;
    txbuff[12] = 0x00;
    txbuff[13] = 0x00;
    txbuff[14] = 0x00;
    txbuff[15] = 0x00;
    txbuff[16] = 0x00;
    txbuff[17] = 0x00;
    txbuff[18] = 0x00;
    txbuff[19] = 0xff;

    for(int i=0;i<19;i++) txbuff[19] = txbuff[19] - txbuff[i];
    SerialPort.write(txbuff,20);

}


void MainWindow::on_btn_send_11_clicked()
{
    QByteArray txbuff;
    txbuff[0] = 0x47;
    txbuff[1] = 0x53;
    txbuff[2] = 0x10;
    txbuff[3] = 0x03;
    txbuff[4] = 0x00;
    txbuff[5] = 0x00;
    txbuff[6] = 0x00;
    txbuff[7] = 0x00;
    txbuff[8] = 0x00;
    txbuff[9] = 0x00;
    txbuff[10] = 0x00;
    txbuff[11] = 0x00;
    txbuff[12] = 0x00;
    txbuff[13] = 0x00;
    txbuff[14] = 0x00;
    txbuff[15] = 0x00;
    txbuff[16] = 0x00;
    txbuff[17] = 0x00;
    txbuff[18] = 0x00;
    txbuff[19] = 0xff;

    for(int i=0;i<19;i++) txbuff[19] = txbuff[19] - txbuff[i];
    SerialPort.write(txbuff,20);
}


void MainWindow::on_btn_send_12_clicked()
{
    QByteArray txbuff;
    txbuff[0] = 0x47;
    txbuff[1] = 0x53;
    txbuff[2] = 0x10;
    txbuff[3] = 0x04;
    txbuff[4] = 0x00;
    txbuff[5] = 0x00;
    txbuff[6] = 0x00;
    txbuff[7] = 0x00;
    txbuff[8] = 0x00;
    txbuff[9] = 0x00;
    txbuff[10] = 0x00;
    txbuff[11] = 0x00;
    txbuff[12] = 0x00;
    txbuff[13] = 0x00;
    txbuff[14] = 0x00;
    txbuff[15] = 0x00;
    txbuff[16] = 0x00;
    txbuff[17] = 0x00;
    txbuff[18] = 0x00;
    txbuff[19] = 0xff;

    for(int i=0;i<19;i++) txbuff[19] = txbuff[19] - txbuff[i];
    SerialPort.write(txbuff,20);
}


void MainWindow::on_btn_send_13_clicked()
{
    QByteArray txbuff;
    txbuff[0] = 0x47;
    txbuff[1] = 0x53;
    txbuff[2] = 0x10;
    txbuff[3] = 0x05;
    txbuff[4] = 0x00;
    txbuff[5] = 0x00;
    txbuff[6] = 0x00;
    txbuff[7] = 0x00;
    txbuff[8] = 0x00;
    txbuff[9] = 0x00;
    txbuff[10] = 0x00;
    txbuff[11] = 0x00;
    txbuff[12] = 0x00;
    txbuff[13] = 0x00;
    txbuff[14] = 0x00;
    txbuff[15] = 0x00;
    txbuff[16] = 0x00;
    txbuff[17] = 0x00;
    txbuff[18] = 0x00;
    txbuff[19] = 0xff;

    for(int i=0;i<19;i++) txbuff[19] = txbuff[19] - txbuff[i];
    SerialPort.write(txbuff,20);
}


void MainWindow::on_btn_send_3_clicked()
{
    QByteArray txbuff;
    uint8_t telemetry_tx_buf[20];

    QString text_Pitch_inner_P;
    QString text_Pitch_inner_I;
    QString text_Pitch_inner_D;
    bool ok;
    int flag=1;
            text_Pitch_inner_P= ui->lineEdit_4->displayText();
            Pitch_Inner_P=text_Pitch_inner_P.toFloat(&ok);
            if(!ok)
            {
                ui->lineEdit_4->setText("Invalid value");
                flag=0;
            }

            text_Pitch_inner_I= ui->lineEdit_5->displayText();
            Pitch_Inner_I=text_Pitch_inner_I.toFloat(&ok);
            if(!ok)
            {
                ui->lineEdit_5->setText("Invalid value");
                flag=0;
            }

            text_Pitch_inner_D= ui->lineEdit_6->displayText();
            Pitch_Inner_D=text_Pitch_inner_D.toFloat(&ok);
            if(!ok)
            {
                ui->lineEdit_6->setText("Invalid value");
                flag=0;
            }

            if(flag == 1)
            {

                     txbuff[0] = 0x47;
                     txbuff[1] = 0x53;
                     txbuff[2] = 0x02;

                     *(float*)&telemetry_tx_buf[3] = Pitch_Inner_P;
                     *(float*)&telemetry_tx_buf[7] = Pitch_Inner_I;
                     *(float*)&telemetry_tx_buf[11] = Pitch_Inner_D;

                     txbuff[3] = telemetry_tx_buf[3];
                     txbuff[4] = telemetry_tx_buf[4];
                     txbuff[5] = telemetry_tx_buf[5];
                     txbuff[6] = telemetry_tx_buf[6];
                     txbuff[7] = telemetry_tx_buf[7];
                     txbuff[8] = telemetry_tx_buf[8];
                     txbuff[9] = telemetry_tx_buf[9];
                     txbuff[10] = telemetry_tx_buf[10];
                     txbuff[11] = telemetry_tx_buf[11];
                     txbuff[12] = telemetry_tx_buf[12];
                     txbuff[13] = telemetry_tx_buf[13];
                     txbuff[14] = telemetry_tx_buf[14];
                     txbuff[15] = 0x00;
                     txbuff[16] = 0x00;
                     txbuff[17] = 0x00;
                     txbuff[18] = 0x00;

                     txbuff[19] = 0xff;

                     for(int i=0;i<19;i++) txbuff[19] = txbuff[19] - txbuff[i];

                SerialPort.write(txbuff,20);

}
            \
           }


void MainWindow::on_btn_send_5_clicked()
{
    QByteArray txbuff;
    uint8_t telemetry_tx_buf[20];
    bool ok;
    int flag=1;
    QString text_Roll_outer_P;
    QString text_Roll_outer_I;
    QString text_Roll_outer_D;

    text_Roll_outer_P= ui->lineEdit_7->displayText();
         Roll_Outer_P=text_Roll_outer_P.toFloat(&ok);
         if(!ok)
         {
             ui->lineEdit_7->setText("Invalid value");
             flag=0;
         }

         text_Roll_outer_I= ui->lineEdit_8->displayText();
         Roll_Outer_I=text_Roll_outer_I.toFloat(&ok);
         if(!ok)
         {
             ui->lineEdit_8->setText("Invalid value");
             flag=0;
         }

         text_Roll_outer_D= ui->lineEdit_9->displayText();
         Roll_Outer_D=text_Roll_outer_D.toFloat(&ok);
         if(!ok)
         {
             ui->lineEdit_9->setText("Invalid value");
             flag=0;
         }
         if(flag == 1)
         {

                  txbuff[0] = 0x47;
                  txbuff[1] = 0x53;
                  txbuff[2] = 0x01;

                  *(float*)&telemetry_tx_buf[3] = Roll_Outer_P;
                  *(float*)&telemetry_tx_buf[7] = Roll_Outer_I;
                  *(float*)&telemetry_tx_buf[11] = Roll_Outer_D;

                  txbuff[3] = telemetry_tx_buf[3];
                  txbuff[4] = telemetry_tx_buf[4];
                  txbuff[5] = telemetry_tx_buf[5];
                  txbuff[6] = telemetry_tx_buf[6];
                  txbuff[7] = telemetry_tx_buf[7];
                  txbuff[8] = telemetry_tx_buf[8];
                  txbuff[9] = telemetry_tx_buf[9];
                  txbuff[10] = telemetry_tx_buf[10];
                  txbuff[11] = telemetry_tx_buf[11];
                  txbuff[12] = telemetry_tx_buf[12];
                  txbuff[13] = telemetry_tx_buf[13];
                  txbuff[14] = telemetry_tx_buf[14];
                  txbuff[15] = 0x00;
                  txbuff[16] = 0x00;
                  txbuff[17] = 0x00;
                  txbuff[18] = 0x00;

                  txbuff[19] = 0xff;

                  for(int i=0;i<19;i++) txbuff[19] = txbuff[19] - txbuff[i];

             SerialPort.write(txbuff,20);

}

}


void MainWindow::on_btn_send_6_clicked()
{
    QByteArray txbuff;
    uint8_t telemetry_tx_buf[20];
    bool ok;
    int flag=1;
    QString text_Pitch_outer_P;
    QString text_Pitch_outer_I;
    QString text_Pitch_outer_D;
            text_Pitch_outer_P= ui->lineEdit_10->displayText();
            Pitch_Outer_P=text_Pitch_outer_P.toFloat(&ok);
            if(!ok)
            {
                ui->lineEdit_10->setText("Invalid value");
                flag=0;
            }

            text_Pitch_outer_I= ui->lineEdit_11->displayText();
            Pitch_Outer_I=text_Pitch_outer_I.toFloat(&ok);
            if(!ok)
            {
                ui->lineEdit_11->setText("Invalid value");
                flag=0;
            }

            text_Pitch_outer_D= ui->lineEdit_12->displayText();
            Pitch_Outer_D=text_Pitch_outer_D.toFloat(&ok);
            if(!ok)
            {
                ui->lineEdit_12->setText("Invalid value");
                flag=0;
            }
            if(flag == 1)
            {

                     txbuff[0] = 0x47;
                     txbuff[1] = 0x53;
                     txbuff[2] = 0x03;

                     *(float*)&telemetry_tx_buf[3] =Pitch_Outer_P;
                     *(float*)&telemetry_tx_buf[7] = Pitch_Outer_I;
                     *(float*)&telemetry_tx_buf[11] = Pitch_Outer_D;

                     txbuff[3] = telemetry_tx_buf[3];
                     txbuff[4] = telemetry_tx_buf[4];
                     txbuff[5] = telemetry_tx_buf[5];
                     txbuff[6] = telemetry_tx_buf[6];
                     txbuff[7] = telemetry_tx_buf[7];
                     txbuff[8] = telemetry_tx_buf[8];
                     txbuff[9] = telemetry_tx_buf[9];
                     txbuff[10] = telemetry_tx_buf[10];
                     txbuff[11] = telemetry_tx_buf[11];
                     txbuff[12] = telemetry_tx_buf[12];
                     txbuff[13] = telemetry_tx_buf[13];
                     txbuff[14] = telemetry_tx_buf[14];
                     txbuff[15] = 0x00;
                     txbuff[16] = 0x00;
                     txbuff[17] = 0x00;
                     txbuff[18] = 0x00;

                     txbuff[19] = 0xff;

                     for(int i=0;i<19;i++) txbuff[19] = txbuff[19] - txbuff[i];

                SerialPort.write(txbuff,20);

   }
}


void MainWindow::on_btn_send_7_clicked()
{
    QByteArray txbuff;
    uint8_t telemetry_tx_buf[20];
    bool ok;
    int flag=1;
    QString text_yaw_heading_P;
    QString text_yaw_heading_I;
    QString text_yaw_heading_D;
            text_yaw_heading_P= ui->lineEdit_13->displayText();
            Yaw_heading_P=text_yaw_heading_P.toFloat(&ok);
            if(!ok)
            {
                ui->lineEdit_13->setText("Invalid value");
                flag=0;
            }

            text_yaw_heading_I= ui->lineEdit_14->displayText();
            Yaw_heading_I=text_yaw_heading_I.toFloat(&ok);
            if(!ok)
            {
                ui->lineEdit_14->setText("Invalid value");
                flag=0;
            }

            text_yaw_heading_D= ui->lineEdit_15->displayText();
            Yaw_heading_D=text_yaw_heading_D.toFloat(&ok);
            if(!ok)
            {
                ui->lineEdit_15->setText("Invalid value");
                flag=0;
            }
            if(flag == 1)
            {

                     txbuff[0] = 0x47;
                     txbuff[1] = 0x53;
                     txbuff[2] = 0x04;

                     *(float*)&telemetry_tx_buf[3] =Yaw_heading_P;
                     *(float*)&telemetry_tx_buf[7] =Yaw_heading_I;
                     *(float*)&telemetry_tx_buf[11] =Yaw_heading_D;

                     txbuff[3] = telemetry_tx_buf[3];
                     txbuff[4] = telemetry_tx_buf[4];
                     txbuff[5] = telemetry_tx_buf[5];
                     txbuff[6] = telemetry_tx_buf[6];
                     txbuff[7] = telemetry_tx_buf[7];
                     txbuff[8] = telemetry_tx_buf[8];
                     txbuff[9] = telemetry_tx_buf[9];
                     txbuff[10] = telemetry_tx_buf[10];
                     txbuff[11] = telemetry_tx_buf[11];
                     txbuff[12] = telemetry_tx_buf[12];
                     txbuff[13] = telemetry_tx_buf[13];
                     txbuff[14] = telemetry_tx_buf[14];
                     txbuff[15] = 0x00;
                     txbuff[16] = 0x00;
                     txbuff[17] = 0x00;
                     txbuff[18] = 0x00;

                     txbuff[19] = 0xff;

                     for(int i=0;i<19;i++) txbuff[19] = txbuff[19] - txbuff[i];

                SerialPort.write(txbuff,20);

   }
}


void MainWindow::on_btn_send_8_clicked()
{
    QByteArray txbuff;
    uint8_t telemetry_tx_buf[20];
    bool ok;
    int flag=1;

    QString text_yaw_rate_P;
    QString text_yaw_rate_I;
    QString text_yaw_rate_D;

            text_yaw_rate_P= ui->lineEdit_16->displayText();
            Yaw_rate_P=text_yaw_rate_P.toFloat(&ok);
            if(!ok)
            {
                ui->lineEdit_16->setText("Invalid value");
                flag=0;
            }

            text_yaw_rate_I= ui->lineEdit_17->displayText();
            Yaw_rate_I=text_yaw_rate_I.toFloat(&ok);
            if(!ok)
            {
                ui->lineEdit_17->setText("Invalid value");
                flag=0;
            }

            text_yaw_rate_D= ui->lineEdit_18->displayText();
            Yaw_rate_D=text_yaw_rate_D.toFloat(&ok);
            if(!ok)
            {
                ui->lineEdit_18->setText("Invalid value");
                flag=0;
            }

            if(flag == 1)
            {

                     txbuff[0] = 0x47;
                     txbuff[1] = 0x53;
                     txbuff[2] = 0x05;

                     *(float*)&telemetry_tx_buf[3] =Yaw_rate_P;
                     *(float*)&telemetry_tx_buf[7] =Yaw_rate_I;
                     *(float*)&telemetry_tx_buf[11] =Yaw_rate_D;

                     txbuff[3] = telemetry_tx_buf[3];
                     txbuff[4] = telemetry_tx_buf[4];
                     txbuff[5] = telemetry_tx_buf[5];
                     txbuff[6] = telemetry_tx_buf[6];
                     txbuff[7] = telemetry_tx_buf[7];
                     txbuff[8] = telemetry_tx_buf[8];
                     txbuff[9] = telemetry_tx_buf[9];
                     txbuff[10] = telemetry_tx_buf[10];
                     txbuff[11] = telemetry_tx_buf[11];
                     txbuff[12] = telemetry_tx_buf[12];
                     txbuff[13] = telemetry_tx_buf[13];
                     txbuff[14] = telemetry_tx_buf[14];
                     txbuff[15] = 0x00;
                     txbuff[16] = 0x00;
                     txbuff[17] = 0x00;
                     txbuff[18] = 0x00;

                     txbuff[19] = 0xff;

                     for(int i=0;i<19;i++) txbuff[19] = txbuff[19] - txbuff[i];

                SerialPort.write(txbuff,20);

   }
}


void MainWindow::on_pushButton_2_clicked()
{
    flag_PlotTimer = true;
     //setpoint=0;
     //SerialPort->close();
     //ui->customPlot->xAxis->setTicker(0);
     ui->customplot->removeGraph(0);
     ui->customplot->removeGraph(1);
     Setup_Grap();
     //SerialPort->open(QIODevice::ReadWrite);
}

