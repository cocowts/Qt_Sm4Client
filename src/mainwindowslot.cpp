#include "mainwindow.h"
#include <QMessageBox>
#include <QByteArray>

#include "sm4/sm4.h"

#include <QDebug>

void MainWindow::showMessage(const QString& title, const QString& text)
{
    QMessageBox(QMessageBox::Information, title, text, QMessageBox::Ok, this, Qt::Drawer).exec();
}

int MainWindow::sm4PKCS7Padding(QByteArray& array)
{
    char fill_len = 16 - ( array.length()%16 == 0 ? 0 : array.length()%16);

    array.resize(array.length() + fill_len);

    for(int i=0; i<fill_len; i++)
    {
        array[array.length() - fill_len + i] = fill_len;
    }

    return array.length();
}

int MainWindow::sm4PKCS7Restore(QByteArray& array)
{
    array.resize(array.length() - array.at(array.length()-1));

    return array.length();
}

void MainWindow::slot_encBtnClicked()
{
    /* 1. 名文数据检查 */
    QByteArray dec_array = m_decEdit->toPlainText().toLatin1();
    if (dec_array.length() == 0)
    {
        showMessage("明文错误", "请输入明文数据");
        return;
    }

    /* 2. 密钥检查 */
    QByteArray key_array = QByteArray::fromHex(m_keyedit->text().toLatin1());
    if (key_array.length() != 16)
    {
        showMessage("密钥错误", "请以 HEX 方式输入 16Bytes 密钥数据");
        return;
    }

    /* 3. 向量检查 */
    QByteArray vector_array = QByteArray::fromHex(m_vectoredit->text().toLatin1());
    if (m_cbc_rbtn->isChecked() && vector_array.length() != 16)
    {
        showMessage("向量错误", "请以 HEX 方式输入 16Bytes 向量数据");
        return;
    }

    /* 4. 数据加密 */
    unsigned char* pkey = reinterpret_cast<unsigned char*>(malloc(static_cast<size_t>(key_array.length())));
    unsigned char* penc = reinterpret_cast<unsigned char*>(malloc(static_cast<size_t>(dec_array.length()) + 16));
    unsigned char* pdec = reinterpret_cast<unsigned char*>(malloc(static_cast<size_t>(dec_array.length()) + 16));

    memcpy(pkey, key_array.constData(), static_cast<size_t>(key_array.length()));
    memcpy(pdec, dec_array.constData(), static_cast<size_t>(dec_array.length()));

    unsigned int len_t = 0;

    if (m_cbc_rbtn->isChecked())
    {
        unsigned char* pvector = reinterpret_cast<unsigned char*>(malloc(static_cast<size_t>(vector_array.length())));
        memcpy(pvector, vector_array.constData(), static_cast<size_t>(vector_array.length()));
        len_t = sm4_cbc(pkey, 0, 1, pvector, static_cast<unsigned int>(dec_array.length()),pdec, penc);
        free(pvector);
    }
    else
    {
        len_t = sm4_ecb(pkey, 0, 1, static_cast<unsigned int>(dec_array.length()),pdec, penc);
    }

    /* 5. 数据显示 */
    m_encEdit->clear();

    for(unsigned int i=0; i<len_t; i++)
    {
        m_encEdit->insertPlainText(QString("%1").arg(penc[i], 2, 16,  QLatin1Char('0')));
    }

    free(pkey);
    free(penc);
    free(pdec);
}

void MainWindow::slot_decBtnClicked()
{
    /* 1. 密文据检查 */
    QByteArray enc_array = QByteArray::fromHex(m_encEdit->toPlainText().toLatin1());
    if ((enc_array.length() == 0) || (enc_array.length() % 16) != 0)
    {
        showMessage("密文错误", "请以 HEX 方式输入 16Bytes 整数倍密文数据");
        return;
    }

    /* 2. 密钥检查 */
    QByteArray key_array = QByteArray::fromHex(m_keyedit->text().toLatin1());
    if (key_array.length() != 16)
    {
        showMessage("密钥错误", "请以 HEX 方式输入 16Bytes 密钥数据");
        return;
    }

    /* 3. 向量检查 */
    QByteArray vector_array = QByteArray::fromHex(m_vectoredit->text().toLatin1());
    if (m_cbc_rbtn->isChecked() && vector_array.length() != 16)
    {
        showMessage("向量错误", "请以 HEX 方式输入 16Bytes 向量数据");
        return;
    }

    /* 4. 数据解密 */
    unsigned char* pkey = reinterpret_cast<unsigned char*>(malloc(static_cast<size_t>(key_array.length())));
    unsigned char* penc = reinterpret_cast<unsigned char*>(malloc(static_cast<size_t>(enc_array.length())));

    memcpy(pkey, key_array.constData(), static_cast<size_t>(key_array.length()));
    memcpy(penc, enc_array.constData(), static_cast<size_t>(enc_array.length()));

    unsigned int len_t = 0;
    if (m_cbc_rbtn->isChecked())
    {
        unsigned char* pvector = reinterpret_cast<unsigned char*>(malloc(static_cast<size_t>(vector_array.length())));
        memcpy(pvector, vector_array.constData(), static_cast<size_t>(vector_array.length()));
        len_t = sm4_cbc(pkey, 1, 1, pvector, static_cast<unsigned int>(enc_array.length()),penc, penc);
        free(pvector);
    }
    else
    {
        len_t = sm4_ecb(pkey, 1, 1, static_cast<unsigned int>(enc_array.length()),penc, penc);
    }

    /* 5. 数据显示 */
    QByteArray dec_array;
    dec_array.resize(static_cast<int>(len_t));
    for(int i=0; i<static_cast<int>(len_t); i++)
        dec_array[i] = static_cast<char>(penc[i]);

    m_decEdit->clear();
        m_decEdit->insertPlainText(dec_array);

    free(pkey);
    free(penc);
}

