#ifndef FILE_PROCESSING_H
#define FILE_PROCESSING_H

#include <QObject>
#include <QFileDialog>

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

    QString getFilename() const;
    void setFilename(const QString &newFilename);

    double getProgress() const;
    void setProgress(double newProgress);
    void resetCountWords();
    void resetWords();
    void resetProgress();

public slots:
    void cancelFunction();
    void setPause(bool temp_pause);
    void setCancel(bool temp_cancel);
    void setStart(bool temp_start);
    bool getPause();
    bool getStart();
    void startFunction();
    void openFuntion();
    double getHeight() {return m_Height;}

signals:
    void Top_CountWords_inFileChanged();
    void Top_Words_inFileChanged();
    void ProgressChanged();
    void FilenameChanged();

private:
    QVector<int> m_Top_CountWords_inFile;
    QVector<QString> m_Top_Words_inFile;
    double m_Progress;
    QString m_Filename;
    QString path;
    bool Cancel;
    bool Pause;
    bool Start;
    QFile file;
    double m_Height;
};

#endif // FILE_PROCESSING_H
