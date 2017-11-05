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
    ~MainWindow();

signals:
    void playButtonPushed();
    void pauseButtonPushed();
    void nextButtonPushed();
    void prevButtonPushed();
    void audioSwitched(size_t audioPosition);
    void addAudioFromDisk();
    void saveAsPlaylist(const QStringListModel* audioListModel);

private:
    Ui::MainWindow *ui;
    QStringListModel *audioListModel;
    QStringListModel *playlistModel;
};

#endif // MAINWINDOW_H
