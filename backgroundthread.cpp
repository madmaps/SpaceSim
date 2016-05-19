#include "backgroundthread.h"

BackgroundThread::BackgroundThread(QObject *parent) :
    QThread(parent)
{
    isDoneUpdating = true;
    stopped = 1;
}

void BackgroundThread::stop()
{
    stopped = 1;
}

bool BackgroundThread::isRunning()const
{
    return stopped;
}

void BackgroundThread::setUpdate()
{
    isDoneUpdating = true;
}

void BackgroundThread::run()
{
    stopped = 0;
    do
    {
        if(isDoneUpdating)
        {
            isDoneUpdating = false;
            updateData();
        }
        msleep(5);
    }while(!stopped);

}
