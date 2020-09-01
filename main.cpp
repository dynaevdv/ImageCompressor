#include <headers/appcontroller.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ImageCompressor::AppController::CreateWindow(800, 600, "main");

    return a.exec();
}
