#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void setAudioListModel(QStringList tracks);
    ~MainWindow();

private slots:
     void on_pushButton_clicked();

signals:
    void play();
    void pause();
    void next();
    void prev();
    void audioSwitched(size_t audioPosition);
    void addAudioFromDisk(MainWindow*);
    void saveAsPlaylist(const QStringListModel* audioListModel);

private:
    Ui::MainWindow *ui;
    QStringListModel *audioListModel;
    QStringListModel *playlistModel;
};

#endif // MAINWINDOW_H
