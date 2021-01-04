#ifndef REQUIREMENTS_H
#define REQUIREMENTS_H

#include <QObject>

class requirements : public QObject
{
    Q_OBJECT
public:
    explicit requirements(QObject *parent = nullptr);

signals:

public slots:
};

#endif // REQUIREMENTS_H