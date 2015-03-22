#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QFileDialog>
#include <QtMultimedia>
#include <QVideoWidget>
#include <QTime>
#include "adapterclass.h"
#include <QFileInfo>
#include <QDebug>
#include <QFile>


namespace Ui {
class MainWindow;
}

class MainWindow :  public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString FileMedia;
    QMediaPlayer * Player;
    quint64 duration;
    QFileinfo *d;
    QVideoWidget *video_widget;
    int playPauseCounter ;

public slots:
    void change_slide_time(qint64);
    void change_duration_time(qint64);

private slots:
    void on_actionOpenFile_triggered();

    void on_PlayPause_clicked();

    void on_Stop_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
