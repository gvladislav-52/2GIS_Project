#include "file_processing.h"
#include <QTimer>
#include <QEventLoop>
#include <QThread>
#include <QtConcurrent>

File_processing::File_processing():m_Progress(0), Cancel(false), Pause(false), m_Height(1)
{
    m_Top_Words_inFile.assign(15,"-");
}

void File_processing::workingWithData()
{
    QHash<QString, int> wordCountMap;
    int currentWord = 0;

    QScopedPointer<QEventLoop> loop(new QEventLoop);
    QScopedPointer<QTimer> timer(new QTimer);

    QVector<QString>::const_iterator it = wordsVector.constBegin();

    while (it != wordsVector.constEnd()) {
        QString word = *it;
        if (getPause()) {
            QTimer::singleShot(1, loop.data(), &QEventLoop::quit);
            loop->exec();
            continue;
        }

        if (Cancel) {
            setCancel();
            break;
        }

        if (word.isEmpty()) {
            ++it;
            continue;
        }

        wordCountMap[word]++;
        currentWord++;

        QList<QString> sortedWords = wordCountMap.keys();
        std::sort(sortedWords.begin(), sortedWords.end(), [&](const QString &w1, const QString &w2) {
            return wordCountMap.value(w1) > wordCountMap.value(w2);
        });

        m_Top_CountWords_inFile.clear();
        m_Top_Words_inFile.clear();

        QVector<QString> topWords = sortedWords.mid(0, qMin(15, sortedWords.size()));
        QVector<int> counts;
        std::transform(topWords.begin(), topWords.end(), std::back_inserter(counts), [&](const QString& word) {
            return wordCountMap.value(word);
        });
        if(counts[0] %75 == 0)
            m_Height = 0.5;

        setProgress(static_cast<double>(currentWord) / wordsVector.size());
        setTop_CountWords_inFile(counts);
        setTop_Words_inFile(topWords);

        timer->setSingleShot(true);
        QObject::connect(timer.data(), &QTimer::timeout, loop.data(), &QEventLoop::quit);
        timer->start(1);
        loop->exec();
        ++it;
    }
}

void File_processing::setCountWords(int &count)
{
    m_Top_CountWords_inFile.append(count);
    emit Top_CountWords_inFileChanged();
}

void File_processing::setWords(QString &word)
{
    m_Top_Words_inFile.append(word);
    emit Top_Words_inFileChanged();
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

void File_processing::setFileName(QString &path)
{
    qDebug() << "ID Function set file path:\t" << QThread::currentThreadId();
    if (!path.isEmpty()) {
        QFileInfo fileInfo(path);
        setFilename(fileInfo.fileName());
    } else {
        qDebug() << "Файл не был выбран.";
    }
}

void File_processing::cancelFunction()
{
    wordsVector.clear();
    path.clear();
    setFilename("");
    resetCountWords();
    resetWords();
    resetProgress();
    Pause = false;
}

void File_processing::setPause()
{
    Pause = !Pause;
}

void File_processing::setCancel()
{
    Cancel = !Cancel;
}

bool File_processing::getPause()
{
    return Pause;
}

void File_processing::startFunction()
{
    QtConcurrent::run([&]() {
        readingFile();
    });
}

void File_processing::openFuntion()
{
    path = QFileDialog::getOpenFileName(nullptr, "Выберите файл", "", "Text Files (*.txt)");
    std::thread t([&](){
        setFileName(path);
    });
    t.join();
}

void File_processing::readingFile()
{
    QHash<QString, int> wordCountMap;
    QString word;
    int currentWord = 0;
    int totalWords = 0;
    qDebug() << "ID Function working with file:" << QThread::currentThreadId();
    //wordsVector.clear();
        file.setFileName(path);
    if (!path.isEmpty()) {
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);

            while (!in.atEnd()) {
                in >> word;
                totalWords++;
            }

            file.seek(0);
            while (!in.atEnd()) {
                wordCountMap[word]++;
                currentWord++;
                in >> word;

               QThread::usleep(100);
                if (getPause())
                {
                    Pause = false;
                    break;
                }

                if((currentWord % 50 == 0) || (currentWord == totalWords))
                {
                QList<QString> sortedWords = wordCountMap.keys();
                std::sort(sortedWords.begin(), sortedWords.end(), [&](const QString &w1, const QString &w2) {
                    return wordCountMap.value(w1) > wordCountMap.value(w2);
                });

                m_Top_CountWords_inFile.clear();
                m_Top_Words_inFile.clear();

                QVector<QString> topWords = sortedWords.mid(0, qMin(15, sortedWords.size()));
                QVector<int> counts;
                std::transform(topWords.begin(), topWords.end(), std::back_inserter(counts), [&](const QString& word) {
                    return wordCountMap.value(word);
                });
                if(counts[0] %75 == 0)
                    m_Height = 0.5;

                setProgress(static_cast<double>(currentWord) / totalWords);
                setTop_CountWords_inFile(counts);
                setTop_Words_inFile(topWords);
                }
            }
        } else {
            qDebug() << "Не удалось открыть файл";
        }
    } else {
        qDebug() << "Сначала выберите файл для открытия!";
    }
    file.close();
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

