#include <headers/appcontroller.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ImageCompressor::AppController::CreateWindow(1700, 1000, "main");

    return a.exec();
}
