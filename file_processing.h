#ifndef FILE_PROCESSING_H
#define FILE_PROCESSING_H

#include <QObject>
#include <QFileDialog>
#include <QDebug>

class File_processing: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVector<int> Top_CountWords_inFile READ getTop_CountWords_inFile WRITE setTop_CountWords_inFile NOTIFY Top_CountWords_inFileChanged FINAL)
    Q_PROPERTY(QVector<QString> Top_Words_inFile READ Top_Words_inFile WRITE setTop_Words_inFile NOTIFY Top_Words_inFileChanged FINAL)

    Q_PROPERTY(double Progress READ getProgress WRITE setProgress NOTIFY ProgressChanged FINAL)
    Q_PROPERTY(QString Filename READ getFilename WRITE setFilename NOTIFY FilenameChanged FINAL)
public:
    File_processing();
    QVector<int> getTop_CountWords_inFile() const;
    void setTop_CountWords_inFile(const QVector<int> &newTop_CountWords_inFile);

    QVector<QString> Top_Words_inFile() const;
    void setTop_Words_inFile(const QVector<QString> &newTop_Words_inFile);

    double getProgress() const;
    void setProgress(double newProgress);
    void resetCountWords();
    void resetWords();
    void resetProgress();

    QString getFilename() const;
    void setFilename(const QString &newFilename);

public slots:
    void chooseFileAndPrintName();
    void setCountWords(int count);
    void setWords(QString word);
    void setFileName(QString path);
    void cancel_Function();
    void setPause();
    void setCancel();
    bool getPause();
    void testFuntc();
    void testFuntc1();
    void testfile(QString &word);

signals:
    void siga();
    void Top_CountWords_inFileChanged();
    void progressChanged(double progress);
    void Top_Words_inFileChanged();
    void ProgressChanged();

    void FilenameChanged();
    void progressUpdated(double progress);

private:
    QVector<int> m_Top_CountWords_inFile;
    QVector<QString> m_Top_Words_inFile;
    double m_Progress;
    QString m_Filename;
    QString path;
    bool Cancel;
    bool Pause;
    double postgres = 0.0;
    bool temp_bo = true;
    int totalWords = 0;
    QFile file;
    QVector<QString> wordsVector;
};



#endif // FILE_PROCESSING_H
