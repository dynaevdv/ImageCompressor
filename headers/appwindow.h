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

#include <algorithm>

#include <headers/filemanager.h>
#include <headers/imagepyramid.h>

namespace ImageCompressor
{
    class AppWindow : public QWidget
    {
        Q_OBJECT

    public:
        AppWindow(const QSize& windowSize, const QString& windowName, QWidget *parent = nullptr);
        ~AppWindow();

    private slots:
        void openAndShowImage();
        void setPyramideLayer(int index);
        void setScaleFactor();
        void setNumberOfFilterIterations();
        void setActivePyramide(int index);

    private:
        QWidget* m_controlBlock;
        QWidget* m_imageBlock;
        QLabel* m_activeLabel;
        ImagePyramide* m_activePyramide = nullptr;
        std::vector<ImagePyramide*> m_pyramides;

        int m_heightOfControlBlock = 50;
        int m_openImageButtonWidth = 130;
        int m_openImageButtonHeight = 30;
        int m_layerComboBoxWidth = 100;
        int m_layerComboBoxHeight = 20;
        int m_spaceBetweenElements = 20;
        int m_comboboxWidth = 150;

        int m_defNumberOfFilterIteration = 1;
        int m_indexOfActiveLayer = 0;
        float m_defScaleFactor = 2.0f;

        void initLayoutWithElements();
        void initImageBlock();
        void initControlBlock();
        void createOpenFileButton();
        void createFileCombobox();
        void createPyramideLayerCombobox();
        void createScaleFactorSpinbox();
        void createFilteringSpinbox();
        void fillLayersCombobox();
        void fillFilenameCombobox();
        void prepareWindowForNewImage();
        void sortPyramidesByDiagonal();
        void addNewPyramide(QPixmap* image, const QString& filepath);
        void renderActivePyramide();
        void areInputFieldsSignalsBlocked(const bool &isBlocked);

        bool isNeedScrollbars(const QSize& imageSize);
    };
}

#endif // MAINWINDOW_H
