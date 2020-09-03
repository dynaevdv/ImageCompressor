#include <headers/appwindow.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ImageCompressor::AppWindow Window(QSize(1900, 1000), "ImageCompressor");
    Window.show();

    return a.exec();
}
