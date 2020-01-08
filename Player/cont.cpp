#include <QFileDialog>
#include <QDir>
#include <QString>
#include <Qtime>

#include "cont.h"
#include "model.h"

Cont::Cont():
    model(new Model())
{

}
void Cont::setupController(Ui::Widget *ui)
{
     model->setupModel(ui);

}
void Cont::add_songs()
{
    QStringList files = QFileDialog::getOpenFileNames(nullptr,
                                                      ("Open files"),
                                                      QString(),
                                                      ("Audio Files (*.mp3)"));
    model->add_songs(files);
}

void Cont::setCurrentIndex(const QModelIndex &index)
{
    model->setCurrentIndex(index);
}

void Cont::previous()
{
     model->previous();
}

void Cont::next()
{
     model->next();
}

void Cont::play()
{
     model->play();
}

void Cont::pause()
{
     model->pause();
}

void Cont::stop()
{
     model->stop();
}

void Cont::volume(int value)
{
     model->volume(value);
}

void Cont::add_playlist()
{
    QString files = QFileDialog::getOpenFileName(nullptr,"Open file",QDir::currentPath(),
                                                 "Playlist files (*.m3u)");
    model->add_playlist(files);
}

void Cont::AddCurrentPlaylist(const QModelIndex &index)
{
    model->AddCurrentPlaylist(index);
}

void Cont::save_playlist()
{
    QString fn = QFileDialog::getSaveFileName(nullptr,"Save file",QDir::currentPath(),
    "Playlist files (*.m3u)");
    model->save_playlist(fn);
}

void Cont::Delete_Song(int countRow, QModelIndexList indexes)
{
    model->Delete_Song(countRow, indexes);
}

void Cont::Delete(int countRow, QModelIndexList indexes)
{
    model->Delete(countRow, indexes);
}

void Cont::Add_to_cur()
{
   model->Add_to_cur();
}

void Cont::exit()
{
    model->save_playlistfree();
}

QTime Cont::Timer(){
    QTime ret = model->Timer();
    return ret;
}


QTime Cont::Timer_now(){
    QTime ret = model->Timer_now();
    return ret;
}

void Cont::info(Ui::Widget *ui){
    model->info(ui);
}

