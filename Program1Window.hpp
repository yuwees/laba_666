#ifndef PROGRAM1WINDOW_HPP
#define PROGRAM1WINDOW_HPP

#include <QMainWindow>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>

class Program1Window : public QMainWindow
{
    Q_OBJECT
public:
    explicit Program1Window(QWidget *parent = nullptr);

private slots:
    void onSelectJsonFile();
    void onLoadFromTxt();
    void onSaveObject();

private:
    void appendToJsonFile(const InkObject &obj);
    void loadJsonArray();

    QLineEdit *m_nameEdit;
    QLineEdit *m_descEdit;
    QLineEdit *m_colorEdit;
    QSpinBox  *m_inkSpin;
    QPushButton *m_selectJsonBtn;
    QPushButton *m_loadTxtBtn;
    QPushButton *m_saveBtn;
    QLabel *m_jsonFileLabel;

    QString m_currentJsonPath;
    QJsonArray m_existingArray;
};

#endif // PROGRAM1WINDOW_HPP
