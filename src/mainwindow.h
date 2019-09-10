#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QLineEdit>
#include <QLabel>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QGridLayout>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    QVBoxLayout* m_vboxlayout;
    QPlainTextEdit* m_encEdit;
    QPlainTextEdit* m_decEdit;

    QLineEdit* m_keyedit;
    QLineEdit* m_vectoredit;

    QRadioButton* m_cbc_rbtn;
    QRadioButton* m_ebc_rbtn;

    QPushButton* m_encbtn;
    QPushButton* m_decbtn;

protected:
    void initUI(void);
    void initSlot(void);

    QGroupBox* initEncUI();
    QGroupBox* initDecUI();
    QGroupBox* initParamUI();

    void showMessage(const QString& title, const QString& text);

    int sm4PKCS7Padding(QByteArray& array);
    int sm4PKCS7Restore(QByteArray& array);

protected slots:
    void slot_encBtnClicked();
    void slot_decBtnClicked();
};

#endif // MAINWINDOW_H
