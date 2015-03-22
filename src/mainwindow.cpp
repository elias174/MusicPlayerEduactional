#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileInfo>
#include <QDebug>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //this->Player = new QMediaPlayer;

    this->duration = 0;
    this->playPauseCounter = 1;
    this->video_widget = new QVideoWidget(this);
    ui->LayoutVideo->addWidget(this->video_widget);
    this->video_widget->hide();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpenFile_triggered()
{
    this->FileMedia =  QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    QDir::homePath(),
                                                    tr("Multimedia (*.mp3 *.mp4 *.jpeg)"));

    Adapter *adapter_mult = new Adapter(this->FileMedia,this->video_widget);
    this->Player = adapter_mult->Player;
   // this->Player->setMedia(QUrl::fromLocalFile(this->FileMedia));
   // this->Player->play();
    ui->label_albumArt->setPixmap(QPixmap::fromImage((adapter_mult->AlbumArt)).scaled(QSize(100,90),  Qt::KeepAspectRatio));
    connect(Player,SIGNAL(positionChanged(qint64)),this,SLOT(change_slide_time(qint64)));
    connect(Player,SIGNAL(durationChanged(qint64)),this,SLOT(change_duration_time(qint64)));

    this->Player->play();
    ui->PlayPause->setIcon(QIcon(":/new/prefix1/pause47.png"));
}

void MainWindow::change_slide_time(qint64 currentInfo){
    currentInfo /= 1000;
    ui->TimeSlider->setValue(currentInfo);

    QString tStr;

    QTime currentTime(0,(currentInfo/60)%60, currentInfo%60);
    QTime totalTime(0,(duration/60)%60, duration%60);
    QString format = "mm:ss";
    tStr = currentTime.toString(format) + " / " + totalTime.toString(format);

    ui->label->setText(tStr);
}

void MainWindow::change_duration_time(qint64 currentInfo){
    this->duration = currentInfo/1000;
    ui->TimeSlider->setMaximum(currentInfo/1000);
}

void MainWindow::on_PlayPause_clicked()
{
    if(playPauseCounter == 1){
        ui->PlayPause->setIcon(QIcon(":/new/prefix1/pause47.png"));
        Player->play();
        playPauseCounter = 2;
     }
    else{
        ui->PlayPause->setIcon(QIcon(":/new/prefix1/start3.png"));
        Player->pause();
        playPauseCounter =1;
    }

}

void MainWindow::on_Stop_clicked()
{
    ui->PlayPause->setIcon(QIcon(":/new/prefix1/start3.png"));
    Player->stop();
    this->video_widget->hide();
    playPauseCounter = 1;
}
