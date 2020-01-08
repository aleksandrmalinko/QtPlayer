#ifndef MODEL_H
#define MODEL_H

#include <QStandardItemModel>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "ui_widget.h"

class Model
{
public:

    Model();
    void setupModel(Ui::Widget *ui);
    void add_songs(QStringList files);
    void setCurrentIndex(const QModelIndex &index);
    void AddCurrentPlaylist(const QModelIndex &index);
    void previous();
    void next();
    void play();
    void pause();
    void stop();
    void volume(int value);
    void add_playlist(QString files);
    void save_playlist(QString fn);
    void save_playlistfree();
    void add_playlistfree();
    void Delete_Song(int countRow, QModelIndexList indexes);
    void Delete(int countRow, QModelIndexList indexes);
    void Add_to_cur();
    QTime Timer();
    QTime Timer_now();
    void info(Ui::Widget *ui);
    void Changeinfo(QString author, QString album, QString year, QString genre);


private:

    QStandardItemModel  *m_all_playlists;
    QStandardItemModel  *m_playListModel;   // Модель данных плейлиста для отображения
    QMediaPlayer        *m_player;          // Проигрыватель треков
    QMediaPlaylist      *m_playlist;        // Плейлиста проигрывателя
    QString paths[20];
    QString about[50][3];
    int idx;
    int count;
    int flag;
    qint64 n1;
};

#endif // MODEL_H
