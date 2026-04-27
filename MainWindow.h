#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void onSelectJsonFile();
    void onLoadFromTxt();
    void onSaveObject();
    void onProgram2();

private:
    void appendToJsonFile(const InkObject &obj);
    void loadJsonArray();

    QLineEdit *m_nameEdit;
    QLineEdit *m_surnameEdit;
    QLineEdit *m_heightEdit;
    QLineEdit *m_weightEdit;
    
    QPushButton *m_selectJsonBtn;
    QPushButton *m_loadTxtBtn;
    QPushButton *m_saveBtn;
    QPushButton *m_program2Btn;
    QLabel *m_jsonFileLabel;

    QString m_currentJsonPath;
    QJsonArray m_existingArray;
};

#endif // MAINWINDOW_HPP
