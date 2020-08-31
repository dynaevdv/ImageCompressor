#include <headers/appcontroller.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ImageCompressor::AppController::CreateWindow(1200, 800, "main");

    return a.exec();
}
