#include <headers/imagepyramid.h>

ImageCompressor::ImagePyramide::ImagePyramide(QPixmap* inputPixmap, const QString& pathToImage)
{
    m_sourceSize = inputPixmap->size();
    m_pathToFile = pathToImage;
    m_pyramide.push_back(new QImage(inputPixmap->toImage()));
    calculatePyramide();
}

ImageCompressor::ImagePyramide::~ImagePyramide()
{
    for (auto image : m_pyramide)
    {
        delete(image);
    }

    m_pyramide.clear();
}

QImage* ImageCompressor::ImagePyramide::GetLayerFromPyramide(const int &index)
{
    qDebug() << "Getlayer:" << index;
    return m_pyramide[index];
}

void ImageCompressor::ImagePyramide::SetScaleFactor(const float &scaleFactor)
{
    m_scaleFactor = scaleFactor;
}

QSize ImageCompressor::ImagePyramide::GetSourceImageSize()
{
    return m_sourceSize;
}

QSize ImageCompressor::ImagePyramide::GetResolutionOfLayer(const int &index)
{
    return m_pyramide[index]->size();
}

int ImageCompressor::ImagePyramide::GetDiagonalOfLayer(const int &index)
{
    auto size = m_pyramide[index]->size();
    return size.width() * size.height();
}

int ImageCompressor::ImagePyramide::GetPyramideSize()
{
    return m_pyramide.size();
}

QString ImageCompressor::ImagePyramide::GetFilename()
{
    QStringList parts = m_pathToFile.split("/");
    return parts.at(parts.size() - 1);
}

QString ImageCompressor::ImagePyramide::GetPathToFile()
{
    return m_pathToFile;
}

void ImageCompressor::ImagePyramide::SetFilePath(const QString &path)
{
    m_pathToFile = path;
}

void ImageCompressor::ImagePyramide::SetNumberOfFiltrationIterations(const int &numberOfIterations)
{
    m_numberOfFiltrationIterations = numberOfIterations;
}

void ImageCompressor::ImagePyramide::calculatePyramide()
{
    QImage* source = m_pyramide[0]; // Source image

    while (source->size().width() > 2 && source->size().height() > 2)
    {
        QImage* tmp1 = new QImage(source->copy());
        ImageCompressor::CompressionManager::Instance().CompressImage(tmp1, m_numberOfFiltrationIterations);
        *tmp1 = tmp1->scaledToHeight((int) (tmp1->size().height() / m_scaleFactor), Qt::SmoothTransformation);
        qDebug() << "Size: " << tmp1->size();
        m_pyramide.push_back(tmp1);
        source = tmp1; // now source is the next layer
    }

    qDebug() << "Number of layers: " << m_pyramide.size();
}
