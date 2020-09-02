#include <headers/mainwindow.h>

ImageCompressor::MainWindow::MainWindow(QSize windowSize, QWidget* parent) : QWidget(parent)
{
    this->setFixedSize(windowSize);

    initControlBlock();
    initImageBlock();
}

ImageCompressor::MainWindow::~MainWindow()
{

}

void ImageCompressor::MainWindow::openAndShowImage()
{
    auto sourcePixMap = FileManager::GetPixmapViaGui();

    // Check for closed GUI or something gone wrong
    if (sourcePixMap != nullptr)
    {
        prepareWindowForNewImage();

        // Hide all images
        auto label = m_imageBlock->findChildren<QLabel*>("label")[0];
        auto area = m_imageBlock->findChildren<QScrollArea*>("area")[0];
        label->hide();
        area->hide();

        // Create Pyramide of images
        m_activePyramide = new ImagePyramid(sourcePixMap,
                                            m_controlBlock->findChildren<QSpinBox*>("filterspinbox")[0]->value(),
                                            m_controlBlock->findChildren<QDoubleSpinBox*>("scalespinbox")[0]->value());

        // Is need scrollarea or a simple label?
        if (isNeedScrollbars(sourcePixMap->size()))
        {
            auto areaLable = area->findChildren<QLabel*>("labelForScroll")[0];
            QImage compressed = *m_activePyramide->GetLayerFromPyramide(m_indexOfActiveLayer);
            areaLable->setPixmap(QPixmap::fromImage(compressed));
            areaLable->resize(m_activePyramide->GetSourceImageSize());
            area->show();

            m_activeLabel = areaLable;
        }
        else
        {
            auto label = m_imageBlock->findChildren<QLabel*>("label")[0];
            QImage compressed = *m_activePyramide->GetLayerFromPyramide(m_indexOfActiveLayer);
            label->setPixmap(QPixmap::fromImage(compressed));
            label->resize(m_activePyramide->GetSourceImageSize());
            label->show();

            m_activeLabel = label;
        }

        fillComboBoxes();

        m_imageBlock->show();
    }
}

void ImageCompressor::MainWindow::setPyramideLayer(int index)
{
    auto layer = QPixmap::fromImage(*m_activePyramide->GetLayerFromPyramide(index));
    layer = layer.scaled(m_activePyramide->GetSourceImageSize(), Qt::AspectRatioMode::KeepAspectRatio);
    m_activeLabel->setPixmap(layer);
    m_activeLabel->resize(m_activePyramide->GetSourceImageSize());
}

void ImageCompressor::MainWindow::setScaleFactor(float scaleFactor)
{
    m_scaleFactor = scaleFactor;
}

void ImageCompressor::MainWindow::setNumberOfFilterIterations(int number)
{
    m_numberOfFilterIteration = number;
}

void ImageCompressor::MainWindow::initControlBlock()
{
    m_controlBlock = new QWidget(this);
    m_controlBlock->setFixedSize(QSize(this->size().width(), m_heightOfControlBlock));
    m_controlBlock->show();

    initLayoutWithElements();
}

void ImageCompressor::MainWindow::initImageBlock()
{
    m_imageBlock = new QWidget(this);
    m_imageBlock->move(m_spaceBetweenElements, m_heightOfControlBlock + m_spaceBetweenElements * 2);
    m_imageBlock->setFixedSize(this->size().width(), this->size().height() - m_heightOfControlBlock - m_spaceBetweenElements);

    // Label for render image
    auto label = new QLabel(m_imageBlock);
    label->setObjectName("label");
    label->hide();

    // Scrollview area and his lable
    auto labelForScroll = new QLabel(m_imageBlock);
    labelForScroll->setObjectName("labelForScroll");
    labelForScroll->hide();

    auto area = new QScrollArea(m_imageBlock);
    area->setObjectName("area");

    area->setFixedSize(this->size().width() - 2 * m_spaceBetweenElements,
                       this->size().height() - 3 * m_spaceBetweenElements - m_heightOfControlBlock);

    area->setWidget(labelForScroll);
    area->hide();
}

void ImageCompressor::MainWindow::initLayoutWithElements()
{
    auto layout = new QHBoxLayout();
    layout->setSpacing(m_spaceBetweenElements);
    m_controlBlock->setLayout(layout);

    createOpenFileButton();
    createPyramideLayerCombobox();
    createFilteringSpinbox();
    createScaleFactorSpinbox();
    layout->addSpacing(800);
}

void ImageCompressor::MainWindow::createOpenFileButton()
{
    auto openFile = new QPushButton();
    openFile->setMinimumHeight(m_openImageButtonHeight);
    openFile->setMinimumWidth(m_openImageButtonWidth);
    m_controlBlock->layout()->addWidget(openFile);
    openFile->setText("Open new image");
    QObject::connect(openFile, SIGNAL (clicked(bool)),
                     this, SLOT(openAndShowImage()));

    openFile->show();
}

void ImageCompressor::MainWindow::createPyramideLayerCombobox()
{
    auto layerComboBox = new QComboBox();
    m_controlBlock->layout()->addWidget(layerComboBox);
    layerComboBox->setMinimumWidth(m_comboboxWidth);
    layerComboBox->setObjectName("layercombobox");
    QObject::connect(layerComboBox, SIGNAL (currentIndexChanged(int)), this, SLOT (setPyramideLayer(int)));
    layerComboBox->show();
}

void ImageCompressor::MainWindow::createScaleFactorSpinbox()
{
    auto spinbox = new QDoubleSpinBox();
    auto label = new QLabel("  ScaleFactor for compressing:");
    m_controlBlock->layout()->addWidget(label);
    m_controlBlock->layout()->addWidget(spinbox);
    spinbox->setObjectName("scalespinbox");
    spinbox->setValue(2.0);
    spinbox->show();
}

void ImageCompressor::MainWindow::createFilteringSpinbox()
{
    auto spinbox = new QSpinBox();
    auto label = new QLabel("  Number of gaussian filtering iterations on each compressing stage:");
    m_controlBlock->layout()->addWidget(label);
    m_controlBlock->layout()->addWidget(spinbox);
    spinbox->setValue(3);
    spinbox->setObjectName("filterspinbox");
    spinbox->show();
}

void ImageCompressor::MainWindow::fillComboBoxes()
{
    // Layer combobox
    auto layercombobox = m_controlBlock->findChildren<QComboBox*>("layercombobox")[0];
    layercombobox->blockSignals(true);
    layercombobox->clear();

    for(int i = 0; i < m_activePyramide->GetPyramideSize(); i++)
    {
        layercombobox->addItem("Layer " +
                               QString::number(i) + ":  " +
                               QString::number(m_activePyramide->GetResolutionOfLayer(i).width()) +
                               "x" +
                               QString::number(m_activePyramide->GetResolutionOfLayer(i).height()));
    }

    layercombobox->blockSignals(false);
}

void ImageCompressor::MainWindow::prepareWindowForNewImage()
{
    if(m_activePyramide)
    {
        delete(m_activePyramide);
    }

    m_indexOfActiveLayer = 0;
}

bool ImageCompressor::MainWindow::isNeedScrollbars(const QSize& imageSize)
{
    if (imageSize.width() >= this->size().width() ||
            imageSize.height() >= this->size().height())
    {
        return true;
    }
    else
    {
        return false;
    }
}

