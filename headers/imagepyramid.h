#ifndef IMAGEPYRAMID_H
#define IMAGEPYRAMID_H

#include <vector>
#include <memory>

#include <QImage>
#include <QPixmap>

#include <headers/compressionmanager.h>

namespace ImageCompressor
{
class ImagePyramid
{
public:
    ImagePyramid(QPixmap* inputPixmap, const QString& pathToFile);
    ~ImagePyramid();

    QImage* GetLayerFromPyramide(const int& index);
    QSize GetSourceImageSize();
    QSize GetResolutionOfLayer(const int& index);
    int GetDiagonalOfLayer(const int& index);
    int GetPyramideSize();
    QString GetFilename();
    QString GetPathToFile();

    void SetFilename(const QString& name);
    void SetNumberOfFiltrationIterations(const int& numberOfIterations);
    void SetScaleFactor(const float& scaleFactor);

private:
    // [0] - source
    std::vector<QImage*> m_pyramide;

    QSize m_sourceSize;
    QString m_filename;
    QString m_pathToFile;
    int m_numberOfFiltrationIterations = 3;
    float m_scaleFactor = 2.0f;

    void calculatePyramide();
};
}

#endif // IMAGEPYRAMID_H
