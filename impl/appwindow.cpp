#include <headers/appwindow.h>

ImageCompressor::AppWindow::AppWindow(QSize windowSize, QWidget* parent) : QWidget(parent)
{
    this->setFixedSize(windowSize);

    initControlBlock();
    initImageBlock();
}

ImageCompressor::AppWindow::~AppWindow()
{

}

void ImageCompressor::AppWindow::openAndShowImage()
{
    QPixmap* sourcePixMap = FileManager::GetPixmapViaGui();

    // Check for closed GUI or something gone wrong
    if (sourcePixMap != nullptr)
    {
        prepareWindowForNewImage();

        // Hide all images
        QLabel* label = m_imageBlock->findChildren<QLabel*>("label")[0];
        QScrollArea* area = m_imageBlock->findChildren<QScrollArea*>("area")[0];
        label->hide();
        area->hide();

        // Create Pyramide of images
        m_pyramides.push_back(new ImagePyramid(sourcePixMap,
                                               ImageCompressor::FileManager::GetLastFilename()));

        m_activePyramide = m_pyramides.back();
        m_activePyramide->SetNumberOfFiltrationIterations(m_numberOfFilterIteration);
        m_activePyramide->SetScaleFactor(m_scaleFactor);

        // Is need scrollarea or a simple label?
        if (isNeedScrollbars(sourcePixMap->size()))
        {
            QLabel* areaLable = area->findChildren<QLabel*>("labelForScroll")[0];
            QImage compressed = *m_activePyramide->GetLayerFromPyramide(m_indexOfActiveLayer);
            areaLable->setPixmap(QPixmap::fromImage(compressed));
            areaLable->resize(m_activePyramide->GetSourceImageSize());
            area->show();

            m_activeLabel = areaLable;
        }
        else
        {
            QLabel* label = m_imageBlock->findChildren<QLabel*>("label")[0];
            QImage compressed = *m_activePyramide->GetLayerFromPyramide(m_indexOfActiveLayer);
            label->setPixmap(QPixmap::fromImage(compressed));
            label->resize(m_activePyramide->GetSourceImageSize());
            label->show();

            m_activeLabel = label;
        }

        fillLayersCombobox();
        fillFilenameCombobox();

        m_imageBlock->show();
    }
}

void ImageCompressor::AppWindow::setPyramideLayer(int index)
{
    QPixmap layer = QPixmap::fromImage(*m_activePyramide->GetLayerFromPyramide(index));
    layer = layer.scaled(m_activePyramide->GetSourceImageSize(), Qt::AspectRatioMode::KeepAspectRatio);
    m_activeLabel->setPixmap(layer);
    m_activeLabel->resize(m_activePyramide->GetSourceImageSize());
}

void ImageCompressor::AppWindow::setScaleFactor(float scaleFactor)
{
    m_scaleFactor = scaleFactor;
}

void ImageCompressor::AppWindow::setNumberOfFilterIterations(int number)
{
    m_numberOfFilterIteration = number;
}

void ImageCompressor::AppWindow::setActivePyramide(int index)
{
    m_activePyramide = m_pyramides[index];
    QPixmap layer = QPixmap::fromImage(*m_activePyramide->GetLayerFromPyramide(index));
    layer = layer.scaled(m_activePyramide->GetSourceImageSize(), Qt::AspectRatioMode::KeepAspectRatio);
    m_activeLabel->setPixmap(layer);
    m_activeLabel->resize(m_activePyramide->GetSourceImageSize());
}

void ImageCompressor::AppWindow::initControlBlock()
{
    m_controlBlock = new QWidget(this);
    m_controlBlock->setFixedSize(QSize(this->size().width(), m_heightOfControlBlock));
    m_controlBlock->show();

    initLayoutWithElements();
}

void ImageCompressor::AppWindow::initImageBlock()
{
    m_imageBlock = new QWidget(this);
    m_imageBlock->move(m_spaceBetweenElements, m_heightOfControlBlock + m_spaceBetweenElements * 2);
    m_imageBlock->setFixedSize(this->size().width(),
                               this->size().height() - m_heightOfControlBlock - m_spaceBetweenElements);

    // Label for render image
    QLabel* label = new QLabel(m_imageBlock);
    label->setObjectName("label");
    label->hide();

    // Scrollview area and his lable
    QLabel* labelForScroll = new QLabel(m_imageBlock);
    labelForScroll->setObjectName("labelForScroll");
    labelForScroll->hide();

    QScrollArea* area = new QScrollArea(m_imageBlock);
    area->setObjectName("area");

    area->setFixedSize(this->size().width() - 2 * m_spaceBetweenElements,
                       this->size().height() - 3 * m_spaceBetweenElements - m_heightOfControlBlock);

    area->setWidget(labelForScroll);
    area->hide();
}

void ImageCompressor::AppWindow::initLayoutWithElements()
{
    QHBoxLayout* layout = new QHBoxLayout();
    layout->setSpacing(m_spaceBetweenElements);
    m_controlBlock->setLayout(layout);

    createOpenFileButton();
    createFileCombobox();
    createPyramideLayerCombobox();
    createFilteringSpinbox();
    createScaleFactorSpinbox();

    layout->addSpacing(this->size().width() / 2);
}

void ImageCompressor::AppWindow::createOpenFileButton()
{
    QPushButton* openFile = new QPushButton();
    openFile->setMinimumHeight(m_openImageButtonHeight);
    openFile->setMinimumWidth(m_openImageButtonWidth);
    m_controlBlock->layout()->addWidget(openFile);
    openFile->setText("Open new image");
    QObject::connect(openFile, SIGNAL (clicked(bool)),
                     this, SLOT(openAndShowImage()));

    openFile->show();
}

void ImageCompressor::AppWindow::createFileCombobox()
{
    QComboBox* fileComboBox = new QComboBox();
    m_controlBlock->layout()->addWidget(fileComboBox);
    fileComboBox->setMinimumWidth(m_comboboxWidth);
    fileComboBox->setObjectName("filecombobox");
    QObject::connect(fileComboBox, SIGNAL (currentIndexChanged(int)), this, SLOT (setActivePyramide(int)));
    fileComboBox->show();
}

void ImageCompressor::AppWindow::createPyramideLayerCombobox()
{
    QComboBox* layerComboBox = new QComboBox();
    m_controlBlock->layout()->addWidget(layerComboBox);
    layerComboBox->setMinimumWidth(m_comboboxWidth);
    layerComboBox->setObjectName("layercombobox");
    QObject::connect(layerComboBox, SIGNAL (currentIndexChanged(int)), this, SLOT (setPyramideLayer(int)));
    layerComboBox->show();
}

void ImageCompressor::AppWindow::createScaleFactorSpinbox()
{
    QDoubleSpinBox* spinbox = new QDoubleSpinBox();
    QLabel* label = new QLabel("  ScaleFactor for compressing:");
    m_controlBlock->layout()->addWidget(label);
    m_controlBlock->layout()->addWidget(spinbox);
    spinbox->setObjectName("scalespinbox");
    spinbox->setValue(2.0);
    spinbox->show();
}

void ImageCompressor::AppWindow::createFilteringSpinbox()
{
    QSpinBox* spinbox = new QSpinBox();
    QLabel* label = new QLabel("  Number of gaussian filtering iterations on each compressing stage:");
    m_controlBlock->layout()->addWidget(label);
    m_controlBlock->layout()->addWidget(spinbox);
    spinbox->setValue(3);
    spinbox->setObjectName("filterspinbox");
    spinbox->show();
}

void ImageCompressor::AppWindow::fillLayersCombobox()
{
    QComboBox* layercombobox = m_controlBlock->findChildren<QComboBox*>("layercombobox")[0];
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

void ImageCompressor::AppWindow::fillFilenameCombobox()
{
    QComboBox* combobox = m_controlBlock->findChildren<QComboBox*>("filecombobox")[0];
    combobox->blockSignals(true);
    combobox->clear();

    // Sort by resolution of sourceimage
    std::map<int, QString> pyramides; // diagonal - filename

    // Fill our map
    for (auto pyramide : m_pyramides)
    {
        pyramides.insert(std::make_pair<int, QString>(pyramide->GetDiagonalOfLayer(0),
                                                      pyramide->GetFilename()));
    }

    // Fill combobox with sorted dictionary
    for (auto iter = pyramides.begin(); iter != pyramides.end(); iter++)
    {
        combobox->addItem(iter->second);
    }
}

void ImageCompressor::AppWindow::prepareWindowForNewImage()
{
    m_indexOfActiveLayer = 0;
}

bool ImageCompressor::AppWindow::isNeedScrollbars(const QSize& imageSize)
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

