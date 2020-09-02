#include <headers/imagepyramid.h>

ImageCompressor::ImagePyramid::ImagePyramid(QPixmap* inputPixmap, const QString& pathToImage)
{
    m_sourceSize = inputPixmap->size();
    m_pathToFile = pathToImage;
    m_pyramide.push_back(new QImage(inputPixmap->toImage()));
    calculatePyramide();
}

ImageCompressor::ImagePyramid::~ImagePyramid()
{
    for (auto image : m_pyramide)
    {
        delete(image);
    }

    m_pyramide.clear();
}

QImage* ImageCompressor::ImagePyramid::GetLayerFromPyramide(const int &index)
{
    qDebug() << "Getlayer:" << index;
    return m_pyramide[index];
}

void ImageCompressor::ImagePyramid::SetScaleFactor(const float &scaleFactor)
{
    m_scaleFactor = scaleFactor;
}

QSize ImageCompressor::ImagePyramid::GetSourceImageSize()
{
    return m_sourceSize;
}

QSize ImageCompressor::ImagePyramid::GetResolutionOfLayer(const int &index)
{
    return m_pyramide[index]->size();
}

int ImageCompressor::ImagePyramid::GetDiagonalOfLayer(const int &index)
{
    auto size = m_pyramide[index]->size();
    return size.width() * size.height();
}

int ImageCompressor::ImagePyramid::GetPyramideSize()
{
    return m_pyramide.size();
}

QString ImageCompressor::ImagePyramid::GetFilename()
{
    QStringList parts = m_pathToFile.split("/");
    return parts.at(parts.size() - 1);
}

QString ImageCompressor::ImagePyramid::GetPathToFile()
{
    return m_pathToFile;
}

void ImageCompressor::ImagePyramid::SetFilename(const QString &name)
{
    m_filename = name;
}

void ImageCompressor::ImagePyramid::SetNumberOfFiltrationIterations(const int &numberOfIterations)
{
    m_numberOfFiltrationIterations = numberOfIterations;
}

void ImageCompressor::ImagePyramid::calculatePyramide()
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
