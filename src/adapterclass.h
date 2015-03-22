#ifndef ADAPTERCLASS
#define ADAPTERCLASS

#include <QString>
#include <QtMultimedia>
#include <QTime>
#include <QImage>
#include <QFileInfo>
#include <QVideoWidget>
//#include <tag
#include <taglib/fileref.h>
#include <taglib/id3v2frame.h>
#include <taglib/id3v2tag.h>
#include <taglib/mpegfile.h>
#include <taglib/id3v2header.h>
#include <taglib/attachedpictureframe.h>

//#include <taglib/

#include "mainwindow.h"

class MultimediaFile{
public:
    QString file_name;
    QMediaPlayer player;
    virtual void playAudio(){}
    virtual void playVideo(){}
    virtual QImage getCoverAlbum(){}
};

class AudioFile : public MultimediaFile
{
public:

    AudioFile(QString file_name){
        this->file_name = file_name;

    }
    QImage getCoverAlbum(){
        TagLib::MPEG::File f(this->file_name.toStdString().c_str());
        TagLib::ID3v2::Tag *m_tag = f.ID3v2Tag();

        TagLib::ID3v2::FrameList frameListMap = m_tag->frameListMap()["APIC"];

        if(frameListMap.isEmpty()) {
            return QImage();
        }

        TagLib::ID3v2::AttachedPictureFrame *coverImg = static_cast<TagLib::ID3v2::AttachedPictureFrame *>(frameListMap.front());

        QImage coverQImg;
        coverQImg.loadFromData((const uchar *) coverImg->picture().data(), coverImg->picture().size());

        return coverQImg;
    }

    void playAudio(){
        this->player.setMedia(QUrl::fromLocalFile(this->file_name));
    }

};

class VideoFile : public MultimediaFile
{
public:

    VideoFile(QString file_name){
        this->file_name = file_name;
    }

    void playVideo(){
        this->player.setMedia(QUrl::fromLocalFile(this->file_name));
    }

};


class Adapter
{
public:
    QMediaPlayer *Player;
    MultimediaFile *file_multimedia;
    QString file_name;
    QImage AlbumArt;
    QVideoWidget *video_widget;
    Adapter( QString file_name, QVideoWidget *video_widget ) {
        this->video_widget = video_widget;
        this->file_name = file_name;

        QFileInfo info1(this->file_name);
        if(info1.completeSuffix() == "mp3"){
            file_multimedia = new AudioFile(this->file_name);
            file_multimedia->playAudio();
            this->AlbumArt = file_multimedia->getCoverAlbum();
            this->Player = &(file_multimedia->player);
        }
        else if( info1.completeSuffix() == "mp4" ){
            file_multimedia = new VideoFile(this->file_name);
            file_multimedia->playVideo();

            this->Player = &(file_multimedia->player);
            this->Player->setVideoOutput(this->video_widget);
            this->video_widget->show();
        }
    }
};




#endif // ADAPTERCLASS

