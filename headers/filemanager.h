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
        static QPixmap* GetPixmapViaGui();
        static QString GetLastFilename();

    private:
        static QString m_lastFilePath;
        static QString getPathOfImageViaDialog();
    };
}

#endif // FILEMANAGER_H
