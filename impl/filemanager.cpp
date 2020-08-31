#include <headers/filemanager.h>

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

QString ImageCompressor::FileManager::getPathOfImageViaDialog()
{
    return QFileDialog::getOpenFileName(0, "Open Dialog",
                                        "", "*.bmp *.jpg *.png");
}
