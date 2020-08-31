#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <vector>
#include <memory>

#include <QWidget>
#include <QWindow>
#include <QIcon>

#include <headers/mainwindow.h>

namespace ImageCompressor
{
    class AppController
    {
    public:
        static void CreateWindow(const int& windowW, const int& windowH, const char* windowName);

    private:
        static std::unique_ptr<ImageCompressor::MainWindow> m_mainWindow;
        // Can be added vector<unique_ptr<QWidget>> for subwindows
    };
}

#endif // APPCONTROLLER_H
