#include <headers/appcontroller.h>

// Static variables
std::unique_ptr<ImageCompressor::MainWindow> ImageCompressor::AppController::m_mainWindow = nullptr;

void ImageCompressor::AppController::CreateWindow(const int& windowW,
    const int& windowH, const char* windowName)
{
    {
        m_mainWindow = std::make_unique<MainWindow>(QSize(windowW, windowH));
        m_mainWindow->setWindowTitle(windowName);
        m_mainWindow->setObjectName("mainWin");
        m_mainWindow->show();
    }
}


