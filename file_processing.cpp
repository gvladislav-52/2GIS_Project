#include "file_processing.h"
#include <QTimer>
#include <QEventLoop>

File_processing::File_processing():m_Progress(0), Pause(false)
{
    m_Top_Words_inFile.assign(15,"-");
}

void File_processing::chooseFileAndPrintName() {
    if(!path.isEmpty()) {
        QFile file(path);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            QHash<QString, int> wordCountMap;
            int totalWords = 0;
            int currentWord = 0;

            while (!in.atEnd()) {
                QString word;
                in >> word;

                if (!word.isEmpty())
                    totalWords++;
            }

            file.seek(0);

            QEventLoop loop;

            while (!in.atEnd() && !Pause) {

                QString word;
                in >> word;

                if (word.isEmpty())
                    continue;

                wordCountMap[word]++;
                currentWord++;

                double progress = static_cast<double>(currentWord) / totalWords;
                qDebug() << "Progress: " << progress;
                setProgress(progress);

                QTimer timer;
                timer.setSingleShot(true);
                connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
                timer.start(1);
                loop.exec();
            }

            file.close();

            QList<QString> sortedWords = wordCountMap.keys();
            std::sort(sortedWords.begin(), sortedWords.end(), [&](const QString &w1, const QString &w2) {
                return wordCountMap.value(w1) > wordCountMap.value(w2);
            });

            m_Top_CountWords_inFile.clear();
            m_Top_Words_inFile.clear();
            for (int i = 0; i < qMin(15, sortedWords.size()); i++) {
                setCountWords(wordCountMap.value(sortedWords[i]));
                setWords(sortedWords[i]);
            }
        } else {
            qDebug() << "Не удалось открыть файл";
        }
    } else {
        qDebug() << "Сначала выберите файл для открытия!";
    }
}


void File_processing::setCountWords(int count)
{
    m_Top_CountWords_inFile.append(count);
    emit Top_CountWords_inFileChanged();
}

void File_processing::setWords(QString word)
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

void File_processing::setFileName()
{
    path = QFileDialog::getOpenFileName(nullptr, "Выберите файл", "", "Text Files (*.txt)");
    if (!path.isEmpty()) {
        QFileInfo fileInfo(path);
        setFilename(fileInfo.fileName());
    } else {
        qDebug() << "Файл не был выбран.";
    }
}

void File_processing::cancel_Function()
{
    path.clear();
    setFilename("");
    resetCountWords();
    resetWords();
    resetProgress();
}

void File_processing::setPause()
{
    Pause = !Pause;
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
