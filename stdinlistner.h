#ifndef STDINLISTNER_H
#define STDINLISTNER_H

#include <windows.h>
#include <QtCore/QThread>

class stdInListner : public QThread
{
    Q_OBJECT

 public:
     stdInListner(QObject *parent);
     ~stdInListner();

 signals:
     void receivedCommand(const QString &cmd);

 private:
     void run();
     bool ok;
};

#endif // STDINLISTNER_H
