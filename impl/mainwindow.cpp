#include <headers/mainwindow.h>

ImageCompressor::MainWindow::MainWindow(QSize windowSize, QWidget* parent) : QWidget(parent)
{
    this->setFixedSize(windowSize);

    initControlBlock();
    initImageBlock();
}

ImageCompressor::MainWindow::~MainWindow()
{
    for (auto  image : m_loadedImages)
    {
        delete(image);
    }

    m_loadedImages.clear();

    delete(m_controlBlock);
    delete(m_imageBlock);
}

void ImageCompressor::MainWindow::openAndShowImage()
{
    auto pixmap = FileManager::GetPixmapViaGui();

    if (pixmap != nullptr)
    {
        // Hide all images
        auto label = m_imageBlock->findChildren<QLabel*>("label")[0];
        auto area = m_imageBlock->findChildren<QScrollArea*>("area")[0];
        label->hide();
        area->hide();

        if (isNeedScrollbars(pixmap->size()))
        {
            auto areaLable = area->findChildren<QLabel*>("labelForScroll")[0];
            areaLable->setPixmap(*pixmap);
            areaLable->resize(pixmap->size());
            area->show();
        }
        else
        {
            label->setPixmap(*pixmap);
            label->show();
        }

        m_imageBlock->show();
    }
}

void ImageCompressor::MainWindow::initControlBlock()
{
    m_controlBlock = new QWidget(this);
    m_controlBlock->setFixedSize(QSize(this->size().width(), m_heightOfControlBlock));
    m_controlBlock->move(m_spaceBetweenElements, m_spaceBetweenElements);
    m_controlBlock->show();

    // OpenFile button
    auto openFile = new QPushButton(m_controlBlock);
    openFile->setFixedSize(m_openImageButtonWidth, m_heightOfControlBlock);
    openFile->setText("Open new image");
    openFile->show();
    QObject::connect(openFile, SIGNAL (clicked(bool)),
                     this, SLOT(openAndShowImage()));
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

