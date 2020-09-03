#include <headers/imagepyramid.h>

ImageCompressor::ImagePyramide::ImagePyramide(QPixmap* inputPixmap, const QString& pathToImage)
{
    m_sourceSize = inputPixmap->size();
    m_pathToFile = pathToImage;
    m_sourceImage = inputPixmap;
    calculateLayerResolutions();
}

ImageCompressor::ImagePyramide::~ImagePyramide()
{

}

void ImageCompressor::ImagePyramide::SetScaleFactor(const float &scaleFactor)
{
    m_scaleFactor = scaleFactor;
    calculateLayerResolutions();
}

QSize ImageCompressor::ImagePyramide::GetSourceImageSize()
{
    return m_sourceSize;
}

QPixmap ImageCompressor::ImagePyramide::GetPyramideLayer(const int &layerIndex)
{
    QImage tmpImage = m_sourceImage->toImage();

    for (int i = 0; i < layerIndex; i++)
    {
        CompressionManager::Instance().ApplyGaussianFilterToImage(&tmpImage, m_numberOfFiltrationIterations);
        tmpImage = tmpImage.scaled(m_layerResolutions[i + 1], Qt::KeepAspectRatioByExpanding);
    }

    tmpImage = tmpImage.scaled(m_layerResolutions[0], Qt::KeepAspectRatioByExpanding);
    return QPixmap::fromImage(tmpImage);
}

QSize ImageCompressor::ImagePyramide::GetResolutionOfLayer(const int &index)
{
    return m_layerResolutions[index];
}

int ImageCompressor::ImagePyramide::GetDiagonalOfLayer(const int &index)
{
    return m_layerResolutions[index].width() * m_layerResolutions[index].height();
}

int ImageCompressor::ImagePyramide::GetPyramideSize()
{
    return m_layerResolutions.size();
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

void ImageCompressor::ImagePyramide::calculateLayerResolutions()
{
    m_layerResolutions.clear();

    QSize tmp = m_sourceImage->size();
    m_layerResolutions.push_back(tmp); // [0] - source resolution

    while (tmp.width() > 2 && tmp.height() > 2)
    {
        tmp.setWidth((float) tmp.width() / m_scaleFactor);
        tmp.setHeight((float) tmp.height() / m_scaleFactor);
        m_layerResolutions.push_back(tmp);
    }
}
