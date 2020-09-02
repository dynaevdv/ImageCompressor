#include <headers/filemanager.h>

// Static variables
QString ImageCompressor::FileManager::m_lastFilePath;

QPixmap* ImageCompressor::FileManager::GetPixmapViaGui()
{
    QPixmap* tmp = new QPixmap(getPathOfImageViaDialog());

    if (!tmp->isNull())
    {
        return tmp;
    }
    else
    {
        return nullptr;
    }
}

QString ImageCompressor::FileManager::GetLastFilename()
{
    return m_lastFilePath;
}

QString ImageCompressor::FileManager::getPathOfImageViaDialog()
{
    QString path = QFileDialog::getOpenFileName(0, "Open Dialog",
                                        "", "*.bmp *.jpg *.png");

    m_lastFilePath = path;
    return path;
}
