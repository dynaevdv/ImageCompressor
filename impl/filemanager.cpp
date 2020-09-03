#include <headers/filemanager.h>

// Static variables
QString ImageCompressor::FileManager::m_lastFilePath;

QPixmap* ImageCompressor::FileManager::GetPixmapFromFile(QString path)
{
    QPixmap* tmp = new QPixmap(path);

    if (!tmp->isNull())
    {
        return tmp;
    }
    else
    {
        return nullptr;
    }
}

QString ImageCompressor::FileManager::GetLastFileName()
{
    return m_lastFilePath;
}

QString ImageCompressor::FileManager::GetPathOfImageViaDialog()
{
    QString path = QFileDialog::getOpenFileName(0, "Open Dialog",
                                        "", "*.bmp *.jpg *.png");

    m_lastFilePath = path;
    return path;
}
