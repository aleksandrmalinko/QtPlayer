#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "cont.h"
#include "ui_widget.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_btn_add_clicked();              // Слот для обработки добавления треков через диалоговое окно
    void on_btn_play_clicked();

    void on_btn_previous_clicked();

    void on_btn_pause_clicked();

    void on_btn_stop_clicked();

    void on_btn_next_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_playlist_add_button_clicked();

    void on_playlist_save_button_clicked();

    void on_playlistView_doubleClicked(const QModelIndex &index);

    void on_savedtableView_doubleClicked(const QModelIndex &index);

    void on_Add_to_cur_clicked();

    void on_Delete_clicked();

    void on_Delete_Song_clicked();

    void on_red_themes_clicked();

    void on_gray_themes_clicked();

    void on_green_themes_clicked();

    void timerEvent(QTimerEvent *evt);


private:
    Ui::Widget *ui;
    Cont *cont;
    int timerld;
    int timepolzumok;
    QMenu *menu = nullptr;

};

#endif // WIDGET_H
