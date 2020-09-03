#include <headers/compressionmanager.h>

ImageCompressor::CompressionManager::CompressionManager()
{
    m_kernel(0, 0) = 1; m_kernel(0, 1) = 2; m_kernel(0, 2) = 1;
    m_kernel(1, 0) = 2; m_kernel(1, 1) = 4; m_kernel(1, 2) = 2;
    m_kernel(2, 0) = 1; m_kernel(2, 1) = 2; m_kernel(2, 2) = 1;
}

ImageCompressor::CompressionManager &ImageCompressor::CompressionManager::Instance()
{
    static CompressionManager m_instance;
    return m_instance;
}

ImageCompressor::CompressionManager::~CompressionManager()
{

}

void ImageCompressor::CompressionManager::ApplyGaussianFilterToImage(QImage *image, int numOfIterations)
{
    // Check for the end of recursion
    if (numOfIterations > 0)
    {
        auto m_tmpImage = image->copy();

        for(int i = 1; i < m_tmpImage.width() - 1; i++)
        {
            for(int j = 1; j < m_tmpImage.height() - 1; j++)
            {
                float red = 0, green = 0, blue = 0;

                // *****************************************************
                red =
                        m_kernel(0, 0) * qRed(m_tmpImage.pixel(i+1, j+1)) +
                        m_kernel(0, 1) * qRed(m_tmpImage.pixel(i, j+1)) +
                        m_kernel(0, 2) * qRed(m_tmpImage.pixel(i-1, j+1)) +

                        m_kernel(1, 0) * qRed(m_tmpImage.pixel(i+1, j)) +
                        m_kernel(1, 1) * qRed(m_tmpImage.pixel(i, j)) +
                        m_kernel(1, 2) * qRed(m_tmpImage.pixel(i-1, j)) +

                        m_kernel(2, 0) * qRed(m_tmpImage.pixel(i+1, j-1)) +
                        m_kernel(2, 1) * qRed(m_tmpImage.pixel(i, j-1)) +
                        m_kernel(2, 2) * qRed(m_tmpImage.pixel(i-1, j-1));

                // *****************************************************
                green =
                        m_kernel(0, 0) * qGreen(m_tmpImage.pixel(i+1, j+1)) +
                        m_kernel(0, 1) * qGreen(m_tmpImage.pixel(i, j+1)) +
                        m_kernel(0, 2) * qGreen(m_tmpImage.pixel(i-1, j+1)) +

                        m_kernel(1, 0) * qGreen(m_tmpImage.pixel(i+1, j)) +
                        m_kernel(1, 1) * qGreen(m_tmpImage.pixel(i, j)) +
                        m_kernel(1, 2) * qGreen(m_tmpImage.pixel(i-1, j)) +

                        m_kernel(2, 0) * qGreen(m_tmpImage.pixel(i+1, j-1)) +
                        m_kernel(2, 1) * qGreen(m_tmpImage.pixel(i, j-1)) +
                        m_kernel(2, 2) * qGreen(m_tmpImage.pixel(i-1, j-1));

                // *****************************************************
                blue =
                        m_kernel(0, 0) * qBlue(m_tmpImage.pixel(i+1, j+1)) +
                        m_kernel(0, 1) * qBlue(m_tmpImage.pixel(i, j+1)) +
                        m_kernel(0, 2) * qBlue(m_tmpImage.pixel(i-1, j+1)) +

                        m_kernel(1, 0) * qBlue(m_tmpImage.pixel(i+1, j)) +
                        m_kernel(1, 1) * qBlue(m_tmpImage.pixel(i, j)) +
                        m_kernel(1, 2) * qBlue(m_tmpImage.pixel(i-1, j)) +

                        m_kernel(2, 0) * qBlue(m_tmpImage.pixel(i+1, j-1)) +
                        m_kernel(2, 1) * qBlue(m_tmpImage.pixel(i, j-1)) +
                        m_kernel(2, 2) * qBlue(m_tmpImage.pixel(i-1, j-1));

                image->setPixel(i,j, qRgb(red/m_kernelSum, green/m_kernelSum, blue/m_kernelSum));
            }
        }

        ApplyGaussianFilterToImage(image, numOfIterations - 1);
    }
}
