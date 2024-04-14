#ifndef FILETHREAD_H
#define FILETHREAD_H

#include <QThread>
#include "file_processing.h"

class FileThread : public QThread
{
    Q_OBJECT
public:
    explicit FileThread(QObject *parent = nullptr);

protected:
    void run() override;

private:
    File_processing *fileProcessing;
};

#endif // FILETHREAD_H
