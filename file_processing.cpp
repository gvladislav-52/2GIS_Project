#include "file_processing.h"
#include <QtConcurrent>
#include <mutex>

File_processing::File_processing():m_Progress(0), Cancel(false), Pause(false), m_Height(1)
{
    m_Top_Words_inFile.assign(15,"-");
    Start = false;
}

QVector<int> File_processing::getTop_CountWords_inFile() const
{
    return m_Top_CountWords_inFile;
}

void File_processing::setTop_CountWords_inFile(const QVector<int> &newTop_CountWords_inFile)
{
    if (m_Top_CountWords_inFile == newTop_CountWords_inFile)
        return;
    m_Top_CountWords_inFile = newTop_CountWords_inFile;
    emit Top_CountWords_inFileChanged();
}

QVector<QString> File_processing::Top_Words_inFile() const
{
    return m_Top_Words_inFile;
}

void File_processing::setTop_Words_inFile(const QVector<QString> &newTop_Words_inFile)
{
    if (m_Top_Words_inFile == newTop_Words_inFile)
        return;
    m_Top_Words_inFile = newTop_Words_inFile;
    emit Top_Words_inFileChanged();
}

double File_processing::getProgress() const
{
    return m_Progress;
}

void File_processing::setProgress(double newProgress)
{
    if (qFuzzyCompare(m_Progress, newProgress))
        return;
    m_Progress = newProgress;
    emit ProgressChanged();
}

void File_processing::resetCountWords()
{
    m_Top_CountWords_inFile.clear();
    emit Top_CountWords_inFileChanged();
}

void File_processing::resetWords()
{
    m_Top_Words_inFile.clear();
    m_Top_Words_inFile.assign(15,"-");
    emit Top_Words_inFileChanged();
}

void File_processing::resetProgress()
{
    m_Progress = 0.0;
    emit ProgressChanged();
}

void File_processing::cancelFunction()
{
    resetCountWords();
    resetWords();
    resetProgress();
    Pause = false;
    path.clear();
    setFilename("");
}

void File_processing::setPause(bool temp_pause)
{
    Pause = temp_pause;
}

void File_processing::setCancel(bool temp_cancel)
{
    Cancel = temp_cancel;
}

void File_processing::setStart(bool temp_start)
{
    Start = temp_start;
}

bool File_processing::getPause()
{
    return Pause;
}

bool File_processing::getStart()
{
   return Start;
}

void File_processing::startFunction()
{
    QtConcurrent::run([&]()
    {
        std::mutex mtx;
        QHash<QString, int> wordCountMap;
        QString word;
        int currentWord = 0;
        int totalWords = 0;
        qDebug() << "ID Function working with file:" << QThread::currentThreadId();
        file.setFileName(path);
        if (!path.isEmpty()) {
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                setStart(true);
                QTextStream in(&file);

                while (!in.atEnd()) {
                    in >> word;
                    totalWords++;
                }

                file.seek(0);
                while (!in.atEnd()) {
                    if (getPause())
                        continue;

                    if (Cancel) {
                        setCancel(false);
                        break;
                    }

                    in >> word;
                    wordCountMap[word]++;
                    currentWord++;

                    if((currentWord % 50 == 0) || (currentWord == totalWords))
                    {
                        QList<QString> sortedWords = wordCountMap.keys();
                        std::sort(sortedWords.begin(), sortedWords.end(), [&](const QString &w1, const QString &w2) {
                            return wordCountMap.value(w1) > wordCountMap.value(w2);
                        });

                        QVector<QString> topWords = sortedWords.mid(0, qMin(15, sortedWords.size()));
                        QVector<int> counts;
                        std::transform(topWords.begin(), topWords.end(), std::back_inserter(counts), [&](const QString& word) {
                            return wordCountMap.value(word);
                        });
                        if(counts[0] %75 == 0)
                            m_Height = 0.5;

                        mtx.lock();
                        m_Top_CountWords_inFile.clear();
                        m_Top_Words_inFile.clear();

                        setTop_CountWords_inFile(counts);
                        setTop_Words_inFile(topWords);
                        setProgress(static_cast<double>(currentWord) / totalWords);
                        mtx.unlock();
                    }
                }
                setStart(false);
                file.close();
            } else {
                qDebug() << "Не удалось открыть файл";
            }
        } else {
            qDebug() << "Сначала выберите файл для открытия!";
        }
    });
}

void File_processing::openFuntion()
{
    path = QFileDialog::getOpenFileName(nullptr, "Выберите файл", "", "Text Files (*.txt)");
    QtConcurrent::run([&]()
                      {
                          qDebug() << "ID Function set file path:\t" << QThread::currentThreadId();
                          if (!path.isEmpty()) {
                              QFileInfo fileInfo(path);
                              setFilename(fileInfo.fileName());
                          } else {
                              qDebug() << "Файл не был выбран.";
                          }
                      });
}

QString File_processing::getFilename() const
{
    return m_Filename;
}

void File_processing::setFilename(const QString &newFilename)
{
    if (m_Filename == newFilename)
        return;
    m_Filename = newFilename;
    emit FilenameChanged();
}

