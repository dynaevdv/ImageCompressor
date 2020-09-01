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

        void CompressImage(QImage* image, int numOfIterations);

    private:
        CompressionManager();

        // Variables for perfomance optimization
        QImage* m_tmpImage;
        QMatrix3x3 m_kernel;
        float m_kernelSum;
    };
}

#endif // COMPRESSIONMANAGER_H
