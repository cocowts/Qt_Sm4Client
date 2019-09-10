#include "mainwindow.h"

#include <QIcon>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    initUI();
    initSlot();
}

MainWindow::~MainWindow()
{

}

void MainWindow::initUI(void)
{
    QVBoxLayout* m_vboxlayout = new QVBoxLayout(this);

    m_vboxlayout->addWidget(initEncUI());
    m_vboxlayout->addWidget(initDecUI());
    m_vboxlayout->addWidget(initParamUI());

    this->setLayout(m_vboxlayout);
    this->setFixedHeight(340);
    this->setMinimumWidth(540);
    this->setWindowTitle("SM4/PKCS7加解密测试工具 - By TianSong");
    this->setWindowIcon(QIcon(":/pic/pic/logo.png"));
}

void MainWindow::initSlot(void)
{
    connect(m_encbtn, SIGNAL(clicked()), this, SLOT(slot_encBtnClicked()));
    connect(m_decbtn, SIGNAL(clicked()), this, SLOT(slot_decBtnClicked()));
}

QGroupBox* MainWindow::initEncUI()
{
    QGroupBox* enc_box = new QGroupBox("密文：", this);
    QVBoxLayout* layout = new QVBoxLayout(enc_box);

    m_encEdit = new QPlainTextEdit(enc_box);
    m_encEdit->setContextMenuPolicy (Qt::NoContextMenu);

    layout->addWidget(m_encEdit);
    enc_box->setLayout(layout);
    enc_box->setFixedHeight(100);

    return enc_box;
}

QGroupBox* MainWindow::initDecUI()
{
    QGroupBox* dec_box  = new QGroupBox("明文：", this);
    QVBoxLayout* layout = new QVBoxLayout(dec_box);

    m_decEdit = new QPlainTextEdit(dec_box);
    m_decEdit->setContextMenuPolicy (Qt::NoContextMenu);

    layout->addWidget(m_decEdit);
    dec_box->setLayout(layout);
    dec_box->setFixedHeight(100);

    return dec_box;
}

QGroupBox* MainWindow::initParamUI()
{
    QGroupBox* param_box = new QGroupBox("参数：", this);
    QGridLayout* layout  = new QGridLayout(param_box);

    m_keyedit    = new QLineEdit(param_box);
    m_vectoredit = new QLineEdit(param_box);
    m_cbc_rbtn   = new QRadioButton("CBC模式 ", param_box);
    m_ebc_rbtn   = new QRadioButton("EBC模式 ", param_box);
    m_encbtn     = new QPushButton("加  密", param_box);
    m_decbtn     = new QPushButton("解  密", param_box);

    m_keyedit->setMaxLength(64);
    m_vectoredit->setMaxLength(64);
    m_ebc_rbtn->setChecked(true);

    m_cbc_rbtn->setCursor(Qt::PointingHandCursor);
    m_ebc_rbtn->setCursor(Qt::PointingHandCursor);
    m_encbtn->setCursor(Qt::PointingHandCursor);
    m_decbtn->setCursor(Qt::PointingHandCursor);

    layout->addWidget(new QLabel("密钥：", param_box), 0, 0);
    layout->addWidget(m_keyedit, 0, 1);
    layout->addWidget(new QLabel("", param_box), 0, 2);
    layout->addWidget(m_cbc_rbtn, 0, 3);
    layout->addWidget(m_encbtn, 0, 4);

    layout->addWidget(new QLabel("向量：", param_box), 1, 0);
    layout->addWidget(m_vectoredit, 1, 1);
    layout->addWidget(new QLabel("", param_box), 0, 2);
    layout->addWidget(m_ebc_rbtn, 1, 3);
    layout->addWidget(m_decbtn, 1, 4);

    param_box->setLayout(layout);

    return param_box;
}
