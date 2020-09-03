#ifndef IMAGEPYRAMID_H
#define IMAGEPYRAMID_H

#include <vector>
#include <memory>

#include <QImage>
#include <QPixmap>

#include <headers/compressionmanager.h>
#include <headers/filemanager.h>

namespace ImageCompressor
{
class ImagePyramide
{
public:
    ImagePyramide(QPixmap* inputPixmap, const QString& pathToFile);
    ~ImagePyramide();

    QSize GetSourceImageSize();
    QPixmap GetPyramideLayer(const int& layerIndex);
    QSize GetResolutionOfLayer(const int& index);
    int GetDiagonalOfLayer(const int& index);
    int GetPyramideSize();
    QString GetFilename();
    QString GetPathToFile();

    void SetFilePath(const QString& path);
    void SetNumberOfFiltrationIterations(const int& numberOfIterations);
    void SetScaleFactor(const float& scaleFactor);

private:
    // [0] - source
    std::vector<QSize> m_layerResolutions;

    QSize m_sourceSize;
    QPixmap* m_sourceImage;
    QString m_filename;
    QString m_pathToFile;
    int m_numberOfFiltrationIterations = 3;
    float m_scaleFactor = 2.0f;

    void calculateLayerResolutions();
};
}

#endif // IMAGEPYRAMID_H
