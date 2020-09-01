#include <headers/imagepyramid.h>

ImageCompressor::ImagePyramid::ImagePyramid(QPixmap* inputPixmap, const int& numberOfIterations, const float& scaleFactor)
{
    m_sourceSize = inputPixmap->size();
    m_scaleFactor = scaleFactor;
    m_numberOfFiltrationIterations = numberOfIterations;
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

int ImageCompressor::ImagePyramid::GetPyramideSize()
{
    return m_pyramide.size();
}

void ImageCompressor::ImagePyramid::SetNumberOfFiltrationIterations(const int &numberOfIterations)
{
    m_numberOfFiltrationIterations = numberOfIterations;
}

void ImageCompressor::ImagePyramid::calculatePyramide()
{
    QImage* tmp = m_pyramide[0]; // Source image

    int counter = 0;
    while (tmp->size().width() > 2 && tmp->size().height() > 2)
    {
        QImage* tmp1 = new QImage(tmp->copy());
        ImageCompressor::CompressionManager::Instance().CompressImage(tmp1, m_numberOfFiltrationIterations);
        *tmp1 = tmp1->scaledToHeight((int) (tmp1->size().height() / m_scaleFactor), Qt::SmoothTransformation);
        m_pyramide.push_back(tmp1);
        tmp = tmp1;
        counter++;
    }
}
