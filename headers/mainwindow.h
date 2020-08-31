#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPushButton>
#include <QDebug>
#include <QSize>
#include <QPoint>
#include <QLabel>
#include <QHBoxLayout>
#include <QWidget>
#include <QScrollArea>
#include <QSpacerItem>

#include <headers/filemanager.h>

namespace ImageCompressor
{
    class MainWindow : public QWidget
    {
        Q_OBJECT

    public:
        MainWindow(QSize windowSize, QWidget *parent = nullptr);
        ~MainWindow();

    private slots:
        void openAndShowImage();

    private:
        std::vector<QPixmap*> m_loadedImages;
        QWidget* m_controlBlock;
        QWidget* m_imageBlock;

        int m_openImageButtonWidth = 100;
        int m_heightOfControlBlock = 50;
        int m_spaceBetweenElements = 20;

        void initControlBlock();
        void initImageBlock();
        bool isNeedScrollbars(const QSize& imageSize);
    };
}

#endif // MAINWINDOW_H
