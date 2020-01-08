#ifndef CONT_H
#define CONT_H

#include "model.h"
#include "ui_widget.h"

class Cont
{
public:
    Cont();
    void setupController(Ui::Widget *ui);
    void add_songs();
    void setCurrentIndex(const QModelIndex &index);
    void AddCurrentPlaylist(const QModelIndex &index);
    void previous();
    void next();
    void play();
    void pause();
    void stop();
    void volume(int value);
    void add_playlist();
    void save_playlist();
    void Delete_Song(int countRow, QModelIndexList indexes);
    void Delete(int countRow, QModelIndexList indexes);
    void Add_to_cur();
    void exit();
    QTime Timer();
    QTime Timer_now();
    void info(Ui::Widget *ui);
    void Changeinfo(QString author, QString album, QString year, QString genre);

private:
    Model *model;
};

#endif // CONT_H
