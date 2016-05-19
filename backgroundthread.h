#ifndef BACKGROUNDTHREAD_H
#define BACKGROUNDTHREAD_H

#include <QThread>

class BackgroundThread : public QThread
{
    Q_OBJECT
public:
    explicit BackgroundThread(QObject *parent = 0);
    void stop();
    bool isRunning() const;

signals:
    void updateData();

public slots:
    void setUpdate();
protected:
    void run();
private:
    volatile bool stopped;
    bool isDoneUpdating;

};

#endif // BACKGROUNDTHREAD_H
