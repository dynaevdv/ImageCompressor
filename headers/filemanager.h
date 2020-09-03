#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <stdexcept>

#include <QFileDialog>
#include <QDebug>
#include <QPixmap>
#include <QImageReader>

namespace ImageCompressor
{
    class FileManager
    {
    public:
        static QPixmap* GetPixmapFromFile(QString path);
        static QString GetPathOfImageViaDialog();
        static QString GetLastFileName();

    private:
        static QString m_lastFilePath;

    };
}

#endif // FILEMANAGER_H
