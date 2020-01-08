#include "widget.h"
#include "cont.h"
#include <QTime>
#include <QtWinExtras>
#include <QMenu>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    cont(new Cont()),
    timepolzumok(0)
{
    timerld = startTimer(1000);
    ui->setupUi(this);
    cont->setupController(ui);
    menu = new QMenu(this);
}

Widget::~Widget()
{
    cont->exit();
    delete ui;
}

void Widget::on_btn_add_clicked()
{
    cont->add_songs();
}


void Widget::on_btn_previous_clicked()
{
    cont->previous();

}

void Widget::on_btn_play_clicked()
{
    cont->play();

}

void Widget::on_btn_pause_clicked()
{
    cont->pause();
}

void Widget::on_btn_stop_clicked()
{
    cont->stop();
    ui->horizontalSlider_2->setValue(0);
}

void Widget::on_btn_next_clicked()
{
    cont->next();


}


void Widget::on_horizontalSlider_valueChanged(int value)
{
    cont->volume(value);
}

void Widget::on_playlist_add_button_clicked()
{
    cont->add_playlist();
}

void Widget::on_playlist_save_button_clicked()
{
    cont->save_playlist();
}


void Widget::on_playlistView_doubleClicked(const QModelIndex &index)
{
    cont->setCurrentIndex(index);

}

void Widget::on_savedtableView_doubleClicked(const QModelIndex &index)
{
    cont->AddCurrentPlaylist(index);
}


void Widget::on_Add_to_cur_clicked()
{
    cont->Add_to_cur();
}

void Widget::on_Delete_clicked()
{
    QModelIndexList indexes =  ui->savedtableView->selectionModel()->selectedRows();
    int countRow = indexes.count();

    cont->Delete(countRow, indexes);
}

void Widget::on_Delete_Song_clicked()
{
    QModelIndexList indexes =  ui->playlistView->selectionModel()->selectedRows();
    int countRow = indexes.count();

    cont->Delete_Song(countRow, indexes);

}

void Widget::on_red_themes_clicked()
{
    setStyleSheet(QString("QPushButton\
    {background-color: white;\
    border-style: solid;\
    border-width:1px;\
    border-radius:12px;\
    border-color: red;\
    max-width:100px;\
    max-height:100px;\
    min-width:25px;\
    min-height:25px;}\
    QTableView\
    {selection-background-color: qlineargradient(x1: 0, y1: 0, x2: 0.5, y2: 0.5,\
     stop: 0 #FF92BB, stop: 1 #E0FFFF);\
     background-color: #FFC0CB;}\
    QSlider::groove:horizontal \
    {background: red;\
    position: absolute; \
    left: 4px; right: 4px;}\
    QSlider::handle:horizontal  {\
    height: 10px;\
    background: gray;\
    margin: 0 -4px;}\
    QSlider::add-page:horizontal  {\
    background: white;}\
    QSlider::sub-page:horizontal  {\
    background: pink;}"));

}

void Widget::on_gray_themes_clicked()
{
    //setStyleSheet(("border-image:url(./rocket.png);");
    setStyleSheet(("QPushButton{background-image: url(:/buttons/kiss.png);}\
     QTableView{background-image: url(:/buttons/kiss.png);}"));
}

void Widget::on_green_themes_clicked()
{
    setStyleSheet(QString("QPushButton {default style};\
        QTableView {default style};"));

}


void Widget::timerEvent(QTimerEvent *evt)
{
    if (evt->timerId() == timerld)
    {
        QTime datatime = cont->Timer();
        QString data = datatime.toString();
        timepolzumok = 0;
        timepolzumok += datatime.minute()*60 + datatime.second();
        ui->all_time->setText(data);

        QTime time = cont->Timer_now();
        ui->now_time->setText(time.toString());
        int value = time.second();
        if (value!=0){
            int bala = value/(timepolzumok/100);
            ui->horizontalSlider_2->setValue(bala);
        }
    }
     cont->info(ui);
}




