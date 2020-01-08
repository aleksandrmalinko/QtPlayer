#include <QDir>
#include <cstdlib>
#include <QTextStream>
#include <QFile>
#include <QTime>
#include <iostream>
#include <fstream>

#include "model.h"
#include "widget.h"
#include <QMediaMetaData>
#include <QtMultimedia/qmetadatawritercontrol.h>

#define GET_VARIABLE_NAME(Variable) (#Variable)

Model::Model():
    m_all_playlists(new QStandardItemModel()),
    m_playListModel(new QStandardItemModel()),
    m_player(new QMediaPlayer()),
    m_playlist(new QMediaPlaylist(m_player)),
    idx(0),
    count(),
    flag(0),
    n1(0)
{
}
void Model::setupModel(Ui::Widget *ui){

    ui->playlistView->setModel(m_playListModel);
    m_playListModel->setHorizontalHeaderLabels(QStringList()  << ("Audio Track")
                                                            << ("File Path"));
    ui->playlistView->hideColumn(1);    // Скрываем колонку, в которой хранится путь к файлу
    ui->playlistView->verticalHeader()->setVisible(false);                  // Скрываем нумерацию строк
    ui->playlistView->setSelectionBehavior(QAbstractItemView::SelectRows);  // Включаем выделение строк
    ui->playlistView->setSelectionMode(QAbstractItemView::SingleSelection); // Разрешаем выделять только одну строку
    ui->playlistView->setEditTriggers(QAbstractItemView::NoEditTriggers);   // Отключаем редактирование
    // Включаем подгонку размера последней видимой колонки к ширине TableView
    ui->playlistView->horizontalHeader()->setStretchLastSection(true);
    m_player->setPlaylist(m_playlist);          // Устанавливаем плейлист в плеер
    m_player->setVolume(70);                    // Устанавливаем громкость воспроизведения треков
    m_player->positionChanged(100);
    m_playlist->setPlaybackMode(QMediaPlaylist::Loop);  // Устанавливаем циклический режим проигрывания плейлиста

    /*------------------------------------------*/
    ui->savedtableView->setModel(m_all_playlists);
    m_all_playlists->setHorizontalHeaderLabels(QStringList()  << ("Playlists")
                                                            << ("File Path"));
    ui->savedtableView->hideColumn(1);    // Скрываем колонку, в которой хранится путь к файлу
    ui->savedtableView->verticalHeader()->setVisible(false);
    ui->savedtableView->setSelectionBehavior(QAbstractItemView::SelectRows);  // Включаем выделение строк
    ui->savedtableView->setSelectionMode(QAbstractItemView::SingleSelection); // Разрешаем выделять несколько строк
    ui->savedtableView->setEditTriggers(QAbstractItemView::NoEditTriggers);   // Отключаем редактирование
    // Включаем подгонку размера последней видимой колонки к ширине TableView
    ui->savedtableView->horizontalHeader()->setStretchLastSection(true);
    add_playlistfree();
    QFile("D:/Player/autosaved/aut.m3u").remove();
    QFile("D:/Player/autosaved/aut.txt").remove();
}
void Model::add_songs(QStringList files){
    foreach (QString filePath, files) {
        QList<QStandardItem *> items;
        items.append(new QStandardItem(QDir(filePath).dirName()));
        items.append(new QStandardItem(filePath));
        m_playListModel->appendRow(items);
        m_playlist->addMedia(QUrl(filePath));
    }
    count++;

}

void Model::setCurrentIndex(const QModelIndex &index)
{
   m_playlist->setCurrentIndex(index.row());
}

void Model::previous()
{
    m_playlist->previous();
}

void Model::next()
{
    m_playlist->next();
}

void Model::play()
{
    m_player->play();
}

void Model::pause()
{
    m_player->pause();
}

void Model::stop()
{
    m_player->stop();
}
void Model::volume(int value)
{
    m_player->setVolume(value);
}

void Model::add_playlist(QString files)
{

    QList<QStandardItem *> items;

    items.append(new QStandardItem(files));
    m_all_playlists->appendRow(items);
    paths[idx] = files;
    idx++;
}

void Model::AddCurrentPlaylist(const QModelIndex &index)
{
    if (flag==0){
        m_playlist->clear();
    }

    while (m_playListModel->rowCount() > 0)
        m_playListModel->removeRow(0);

    m_playlist->load(QUrl::fromLocalFile(paths[index.row()]),"m3u");
    for (int i=0;i<m_playlist->mediaCount();i++)
    {
        QList<QStandardItem *> items;
        items.append(new QStandardItem(QDir(m_playlist->media(i).canonicalUrl().toString()).dirName()));
        items.append(new QStandardItem(m_playlist->media(i).canonicalUrl().toString()));
        m_playListModel->appendRow(items);
    }
    flag = 0;
}
void Model::save_playlist(QString fn)
{
    m_playlist->save(QUrl::fromLocalFile(fn),"m3u");
}

void Model::save_playlistfree()
{
    QString aut = "D:/Player/autosaved/aut.m3u";
    m_playlist->save(QUrl::fromLocalFile(aut), "m3u");




    QFile file("D:/Player/autosaved/aut.txt");
    int i=0;
    //for (i=0; i<idx; i++) paths[i].chop(1);
    i=0;
    QTextStream out(&file);
    if (file.open((QIODevice::WriteOnly| QIODevice::Text))){
        while (i<idx) {
            int u=0;
            while(1){
                if((paths[i][u]=='3')&&(paths[i][u+1]=='u')){
                    out << paths[i][u];
                    u++;
                    if (i==(idx-1)) out << paths[i][u];
                    else out << paths[i][u]<< "\n";
                    break;
                }
                else {
                    out << paths[i][u];
                    u++;
                }
            }
           i++;
        }
        //i--;
    }
    file.close();


    QFile file2("D:/Player/autosaved/autinf.txt");
    i=0;
    QTextStream out2(&file2);
    if (file2.open((QIODevice::WriteOnly| QIODevice::Text))){
        while (i < count) {
            out2 << about[i][0]<< "\n" << about[i][1]<< "\n" << about[i][2]<< "\n" ;
            i++;
        }
    }
    file2.close();

}

void Model::add_playlistfree()
{
    QString aut = "D:/Player/autosaved/aut.m3u";
    m_playlist->load(QUrl::fromLocalFile(aut),"m3u");
    for (int i=0;i<m_playlist->mediaCount();i++)
    {
        QList<QStandardItem *> items;
        items.append(new QStandardItem(QDir(m_playlist->media(i).canonicalUrl().toString()).dirName()));
        items.append(new QStandardItem(m_playlist->media(i).canonicalUrl().toString()));
        m_playListModel->appendRow(items);
    }


    QFile file("D:/Player/autosaved/aut.txt");
    int i=0;
    if ((file.exists())&&(file.open(QIODevice::ReadOnly))){
        while (!file.atEnd()) {
            QString temp;
            paths[i] = file.readLine();
            int u=0;
            while(1){
                if((paths[i][u]=='3')&&(paths[i][u+1]=='u')){
                    if (paths[i][u+2]==0x0d)
                                paths[i].chop(2);
                    break;
                }
                else
                    u++;
            }
            i++;
        }
        idx=i;
        i=0;
    file.close();
    for (i=0;i<idx;i++){
        QList<QStandardItem *> items2;
        items2.append(new QStandardItem(paths[i]));
        m_all_playlists->appendRow(items2);
    }
    }


    QFile file2("D:/Player/autosaved/autinf.txt");
    i=0;
    if ((file2.exists())&&(file2.open(QIODevice::ReadOnly))){
        while (!file2.atEnd()) {
            for (int j=0; j<3; j++){
                about[i][j] = file2.readLine();
                about[i][j].chop(2);
                }
            i++;
        }
     }
        count=i;
        i=0;
    file2.close();
}

void Model::Delete_Song(int countRow, QModelIndexList indexes)
{
   m_playListModel->removeRow( indexes.at(countRow-1).row(), QModelIndex());
   m_playlist->removeMedia(indexes.at(countRow-1).row());
   count--;
}

void Model::Delete(int countRow, QModelIndexList indexes)
{
    m_all_playlists->removeRow( indexes.at(countRow-1).row(), QModelIndex());
    for (int i=indexes.at(countRow-1).row(); i<idx-1; i++){
        paths[i] = paths[i+1];
    }
    idx--;
}

void Model::Add_to_cur()
{
   flag=1;
}

QTime Model::Timer(){
    n1 = m_player->duration();
    int h = ( n1 / (60*60*1000));
    int m = (( n1 % (60*60*1000)) / (60*1000));
    int s = ((n1 % (60*1000)) /1000);
    return QTime(h,m,s);
}


QTime Model::Timer_now(){
    QTime time(0,0,0,0);
    time = time.addMSecs(m_player->position());
    return time;
}

void Model::info(Ui::Widget *ui){
    if (m_player->isMetaDataAvailable()) {
        QString author = m_player->metaData(QStringLiteral("Author")).toString();
        QString year = m_player->metaData(QStringLiteral("Year")).toString();
        QString genre = m_player->metaData(QStringLiteral("Genre")).toString();

        ui->label_author->setText(author);
        ui->label_year->setText(year);
        ui->label_genre->setText(genre);
    }
}


