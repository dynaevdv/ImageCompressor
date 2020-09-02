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
#include <QComboBox>
#include <QSpinBox>
#include <QSizePolicy>

#include <headers/filemanager.h>
#include <headers/imagepyramid.h>

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
        void setPyramideLayer(int index);
        void setScaleFactor(float scaleFactor);
        void setNumberOfFilterIterations(int number);

    private:
        QWidget* m_controlBlock;
        QWidget* m_imageBlock;
        QLabel* m_activeLabel;
        ImagePyramid* m_activePyramide = nullptr;

        int m_heightOfControlBlock = 50;
        int m_openImageButtonWidth = 130;
        int m_openImageButtonHeight = 40;
        int m_layerComboBoxWidth = 100;
        int m_layerComboBoxHeight = 20;
        int m_spaceBetweenElements = 20;
        int m_comboboxWidth = 150;

        int m_numberOfFilterIteration = 3;
        int m_indexOfActiveLayer = 0;
        float m_scaleFactor = 2.0f;

        void initLayoutWithElements();
        void initImageBlock();
        void initControlBlock();
        void createOpenFileButton();
        void createPyramideLayerCombobox();
        void createScaleFactorSpinbox();
        void createFilteringSpinbox();
        void fillComboBoxes();

        void prepareWindowForNewImage();
        bool isNeedScrollbars(const QSize& imageSize);
    };
}

#endif // MAINWINDOW_H
