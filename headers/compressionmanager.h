#ifndef COMPRESSIONMANAGER_H
#define COMPRESSIONMANAGER_H

#include <QImage>
#include <QMatrix3x3>

namespace ImageCompressor
{
    class CompressionManager
    {
    public:
        static CompressionManager& Instance();
        ~CompressionManager();

        void ApplyGaussianFilterToImage(QImage* image, int numOfIterations);

    private:
        CompressionManager();

        // Variables for perfomance optimization
        QMatrix3x3 m_kernel;
        float m_kernelSum = 16.0f;
    };
}

#endif // COMPRESSIONMANAGER_H
