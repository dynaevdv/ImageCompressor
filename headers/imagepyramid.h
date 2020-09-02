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
    ImagePyramid(QPixmap* inputPixmap, const int& numberOfIterations, const float& scaleFactor);
    ~ImagePyramid();

    QImage* GetLayerFromPyramide(const int& index);
    QSize GetSourceImageSize();
    QSize GetResolutionOfLayer(const int& index);
    int GetPyramideSize();

    void SetNumberOfFiltrationIterations(const int& numberOfIterations);
    void SetScaleFactor(const float& scaleFactor);

private:
    // [0] - source
    std::vector<QImage*> m_pyramide;
    QSize m_sourceSize;
    int m_numberOfFiltrationIterations;
    float m_scaleFactor;

    void calculatePyramide();
};
}

#endif // IMAGEPYRAMID_H
