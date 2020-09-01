#include <headers/appcontroller.h>

// Static variables
ImageCompressor::MainWindow* ImageCompressor::AppController::m_mainWindow = nullptr;

void ImageCompressor::AppController::CreateWindow(const int& windowW,
    const int& windowH, const char* windowName)
{
    {
        m_mainWindow = new MainWindow(QSize(windowW, windowH));
        m_mainWindow->setWindowTitle(windowName);
        m_mainWindow->setObjectName("mainWin");
        m_mainWindow->show();
    }
}

ImageCompressor::AppController::~AppController()
{
    delete(m_mainWindow);
}


