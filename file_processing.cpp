#include "file_processing.h"

File_processing::File_processing():m_Progress(0)
{
    for(int i = 0; i < 15; i++)
    {
        m_Top_CountWords_inFile.append(0);
        m_Top_Words_inFile.append("-");
    }
}

void File_processing::chooseFileAndPrintName() {
    QFile file(QFileDialog::getOpenFileName(nullptr, "Выберите файл"));
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QHash<QString, int> wordCountMap; // QHash для хранения частоты встречаемости слов
        int totalLines = 0;
        int currentLine = 0;
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList words = line.split(" ", Qt::SkipEmptyParts);
            totalLines++;
            for (const QString& word : words)
                wordCountMap[word]++; // Увеличиваем счетчик для текущего слова
            currentLine++;
            setProgress(static_cast<double>(currentLine) / totalLines);
        }

        file.close();
        QList<QString> sortedWords = wordCountMap.keys();
        std::sort(sortedWords.begin(), sortedWords.end(), [&](const QString &w1, const QString &w2) {
            return wordCountMap.value(w1) > wordCountMap.value(w2);
        });

        m_Top_CountWords_inFile.clear();
        m_Top_Words_inFile.clear();
        for(int i = 0; i < 15; i++)
        {
            setCountWords(wordCountMap.value(sortedWords[i]));
            setWords(sortedWords[i]);
        }
    } else {
        qDebug() << "Не удалось открыть файл";
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
