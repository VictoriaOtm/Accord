#ifndef UPLOADWINCONTROLLER_H
#define UPLOADWINCONTROLLER_H

#include <qfiledialog.h>
#include "maincontroller.h"
#include "audio.h"

class UploadWinController : public QObject
{
    Q_OBJECT

public:
    UploadWinController();

public slots:
    void Add(MainWindow*);

signals:
    void TracksAdded(QVector<Audio>);

private:
    QVector<Audio> tracksToAdd;
};

#endif // UPLOADWINCONTROLLER_H
