#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QtGui>
#include <QMessageBox>
#include <QErrorMessage>
#include <QInputDialog>
#include <QLineEdit>
#include <QRadioButton>
#include <memory>

#include "ui_mainwindow.h"
#include "qslider.h"
#include "audio.h"


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setAudioListModel(QStringList tracks);
    void setPlaylistsModel(QStringList playlists);
    void setAudioListModelForPlaylist(QStringList tracks);


    void showErrorMessage(QString textOfError);
    bool getLineOfText(const QString title, const QString message, QString& result);

public slots:
    void sliderPositionChanged(qint64);
    void curAudioDurationChanged(qint64);
    void itemIndexChanged(int);
    void errorMessage(QString);
    void audioRemoveFromList(int);

private slots:
    void ShowContextMenu(const QPoint&);
    void addButtonPushed();
    void removeButtonPushed();

    void setVolumeSlider();

    void itemClickedLeftColumn(QListWidgetItem*);
    void itemClicked(QListWidgetItem*);
    void itemDoubleClicked(QListWidgetItem*);

    void setPrevRow();
    void setNextRow();

signals:
    void play(bool);
    void pause(bool);
    void next();
    void prev();

    void settings();

    void playlistSelected(int);
    void audioSelected(int);
    void audioSwitched(int);

    void addAudioFromDisk(MainWindow*);
    void removeAudio();
    void saveAsPlaylist();

    void loopPlaylist(bool);


private:
    Ui::MainWindow *ui;
    QStringListModel *audioListModel;
    QStringListModel *playlistModel;

    QListWidgetItem *audioListItem;

    QRadioButton *playPauseButton;
    QSlider *volumeSlider;
    bool volumeSliderStatus;
    qint64 curAudioDuration;
};

#endif // MAINWINDOW_H
