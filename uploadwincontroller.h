#ifndef UPLOADWINCONTROLLER_H
#define UPLOADWINCONTROLLER_H

#include <qfiledialog.h>
#include "uploadwindow.h"
#include "maincontroller.h"

class UploadWinController : public QObject
{
    Q_OBJECT

public:
    UploadWinController();

public slots:
    void Add(MainWindow*);

signals:
    void TracksAdded(QStringList);

private:
    UploadWindow uploadWin;
    QStringList tracksToAdd;
};

#endif // UPLOADWINCONTROLLER_H
