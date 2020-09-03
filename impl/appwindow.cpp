#include <headers/appwindow.h>

ImageCompressor::AppWindow::AppWindow(const QSize& windowSize,
                                      const QString& windowName, QWidget* parent) : QWidget(parent)
{
    setFixedSize(windowSize);
    setWindowTitle(windowName);
    initControlBlock();
    initImageBlock();
}

ImageCompressor::AppWindow::~AppWindow()
{

}

void ImageCompressor::AppWindow::openAndShowImage()
{
    QPixmap* sourcePixMap = FileManager::GetPixmapFromFile(FileManager::GetPathOfImageViaDialog());

    // Check for closed GUI or something gone wrong
    if (sourcePixMap != nullptr)
    {
        prepareWindowForNewImage();

        addNewPyramide(sourcePixMap,
                       FileManager::GetLastFileName());

        renderPyramide(m_activePyramide);

        fillLayersCombobox();
        fillFilenameCombobox();
    }
}

void ImageCompressor::AppWindow::setPyramideLayer(int index)
{
    m_activeLabel->setPixmap(m_activePyramide->GetPyramideLayer(index));
    m_activeLabel->resize(m_activePyramide->GetSourceImageSize());
}

void ImageCompressor::AppWindow::setScaleFactor()
{
    qDebug() << "SetScalefactor";
    m_activePyramide->SetScaleFactor(m_controlBlock->findChildren<QDoubleSpinBox*>
                                     ("scalespinbox")[0]->value());

    m_activeLabel->setPixmap(m_activePyramide->GetPyramideLayer(0));
    fillLayersCombobox();
}

void ImageCompressor::AppWindow::setNumberOfFilterIterations()
{
    m_activePyramide->SetNumberOfFiltrationIterations(m_controlBlock->findChildren<QSpinBox*>
                                                      ("filterspinbox")[0]->value());
}

void ImageCompressor::AppWindow::setActivePyramide(int index)
{
    m_activePyramide = m_pyramides[index];

    prepareWindowForNewImage();

    renderPyramide(m_activePyramide);

    fillLayersCombobox();
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
    m_imageBlock->move(m_spaceBetweenElements, m_heightOfControlBlock + m_spaceBetweenElements);
    m_imageBlock->setFixedSize(this->size().width(),
                               this->size().height() - m_heightOfControlBlock - m_spaceBetweenElements);

    // Label for render image
    QLabel* label = new QLabel(m_imageBlock);
    label->setObjectName("label");
    label->hide();

    // Scrollview area and his lable
    QLabel* labelForScroll = new QLabel(m_imageBlock);
    labelForScroll->setObjectName("labelforscroll");
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
    spinbox->setValue(m_defScaleFactor);

    QObject::connect(spinbox, SIGNAL (editingFinished()), this, SLOT (setScaleFactor()));
    spinbox->show();
}

void ImageCompressor::AppWindow::createFilteringSpinbox()
{
    QSpinBox* spinbox = new QSpinBox();
    QLabel* label = new QLabel("  Number of gaussian filtering iterations on each compressing stage:");
    m_controlBlock->layout()->addWidget(label);
    m_controlBlock->layout()->addWidget(spinbox);
    spinbox->setValue(m_defNumberOfFilterIteration);
    spinbox->setObjectName("filterspinbox");

    QObject::connect(spinbox, SIGNAL (editingFinished()), this, SLOT (setNumberOfFilterIterations()));
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

    sortPyramidesByDiagonal();

    for (auto pyramide : m_pyramides)
    {
        combobox->addItem(pyramide->GetFilename());
    }

    // Find index of activepyramide
    for (int i = 0; i < m_pyramides.size(); i++)
    {
        if (m_pyramides[i] == m_activePyramide)
        {
            combobox->setCurrentIndex(i);
        }
    }

    combobox->blockSignals(false);
}

void ImageCompressor::AppWindow::prepareWindowForNewImage()
{
    // Hide all previous images
    QLabel* label = m_imageBlock->findChildren<QLabel*>("label")[0];
    label->clear();
    label->hide();
    QScrollArea* scrollArea = m_imageBlock->findChildren<QScrollArea*>("area")[0];
    label = scrollArea->findChildren<QLabel*>("labelforscroll")[0];
    label->clear();
    scrollArea->hide();

    m_indexOfActiveLayer = 0;
}

void ImageCompressor::AppWindow::sortPyramidesByDiagonal()
{
    struct PyramidesDiagonalComparer
    {
        bool operator() (ImagePyramide* first, ImagePyramide* second)
        {
            return (first->GetDiagonalOfLayer(0) < second->GetDiagonalOfLayer(0));
        }
    };

    std::sort(m_pyramides.begin(), m_pyramides.end(), PyramidesDiagonalComparer());

}

void ImageCompressor::AppWindow::addNewPyramide(QPixmap *image, const QString &filepath)
{
    ImagePyramide* pyramide = new ImagePyramide(image,
                                                ImageCompressor::FileManager::GetLastFileName());

    pyramide->SetNumberOfFiltrationIterations(m_defNumberOfFilterIteration);
    pyramide->SetScaleFactor(m_defScaleFactor);
    pyramide->SetFilePath(filepath);
    m_activePyramide = pyramide;

    m_pyramides.push_back(pyramide);
}

void ImageCompressor::AppWindow::renderPyramide(ImageCompressor::ImagePyramide *pyramide)
{
    // Is need scrollarea or a simple label?
    if (isNeedScrollbars(m_activePyramide->GetSourceImageSize()))
    {
        QScrollArea* area = m_imageBlock->findChildren<QScrollArea*>("area")[0];
        QLabel* areaLable = area->findChildren<QLabel*>("labelforscroll")[0];
        areaLable->setPixmap(m_activePyramide->GetPyramideLayer(0));
        areaLable->resize(m_activePyramide->GetSourceImageSize());
        area->show();

        m_activeLabel = areaLable;
    }
    else
    {
        QLabel* label = m_imageBlock->findChildren<QLabel*>("label")[0];
        label->setPixmap(m_activePyramide->GetPyramideLayer(0));
        label->resize(m_activePyramide->GetSourceImageSize());
        label->show();

        m_activeLabel = label;
    }

    m_imageBlock->show();
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

