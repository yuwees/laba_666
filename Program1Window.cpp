#include "Program1Window.hpp"
#include "InkObject.hpp"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QMessageBox>
#include <QPushButton>

Program1Window::Program1Window(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *central = new QWidget;
    setCentralWidget(central);
    QVBoxLayout *mainLayout = new QVBoxLayout(central);

    // Строка выбора JSON файла
    QHBoxLayout *jsonSelectLayout = new QHBoxLayout;
    m_selectJsonBtn = new QPushButton("Выбрать JSON файл");
    m_jsonFileLabel = new QLabel("Файл не выбран");
    jsonSelectLayout->addWidget(m_selectJsonBtn);
    jsonSelectLayout->addWidget(m_jsonFileLabel, 1);
    mainLayout->addLayout(jsonSelectLayout);

    // Группа "Новый объект"
    QGroupBox *group = new QGroupBox("Новый объект");
    QFormLayout *formLayout = new QFormLayout;

    m_nameEdit = new QLineEdit;
    m_descEdit = new QLineEdit;
    m_colorEdit = new QLineEdit;
    m_inkSpin = new QSpinBox;
    m_inkSpin->setRange(0, 100);
    m_inkSpin->setSuffix(" %");

    formLayout->addRow("Название:", m_nameEdit);
    formLayout->addRow("Описание:", m_descEdit);
    formLayout->addRow("Цвет:", m_colorEdit);
    formLayout->addRow("Уровень чернил:", m_inkSpin);

    m_loadTxtBtn = new QPushButton("ИЗ .ТХТ");
    m_saveBtn = new QPushButton("ОК");

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addWidget(m_loadTxtBtn);
    btnLayout->addWidget(m_saveBtn);

    QVBoxLayout *groupLayout = new QVBoxLayout;
    groupLayout->addLayout(formLayout);
    groupLayout->addLayout(btnLayout);
    group->setLayout(groupLayout);

    mainLayout->addWidget(group);
    mainLayout->addStretch();

    connect(m_selectJsonBtn, &QPushButton::clicked, this, &Program1Window::onSelectJsonFile);
    connect(m_loadTxtBtn, &QPushButton::clicked, this, &Program1Window::onLoadFromTxt);
    connect(m_saveBtn, &QPushButton::clicked, this, &Program1Window::onSaveObject);

    setWindowTitle("Программа 1 – Создание маркера");
    resize(500, 350);
}

void Program1Window::onSelectJsonFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Выберите JSON файл", "", "JSON files (*.json)");
    if (fileName.isEmpty()) return;
    m_currentJsonPath = fileName;
    m_jsonFileLabel->setText(QFileInfo(fileName).fileName());
    loadJsonArray();
}

void Program1Window::loadJsonArray()
{
    m_existingArray = QJsonArray();
    if (m_currentJsonPath.isEmpty()) return;

    QFile file(m_currentJsonPath);
    if (!file.exists()) return;
    if (!file.open(QIODevice::ReadOnly)) return;

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    if (doc.isArray()) {
        m_existingArray = doc.array();
    }
}

void Program1Window::onLoadFromTxt()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Выберите TXT файл", "", "Text files (*.txt)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть TXT файл.");
        return;
    }

    QTextStream in(&file);
    QString line = in.readLine();
    file.close();

    if (line.isEmpty()) {
        QMessageBox::warning(this, "Предупреждение", "Файл пуст.");
        return;
    }

    InkObject obj;
    obj.parseFromTxtLine(line);

    m_nameEdit->setText(obj.getName());
    m_descEdit->setText(obj.getDescription());
    m_colorEdit->setText(obj.getColor());
    if (obj.getInkLevel() >= 0 && obj.getInkLevel() <= 100) {
        m_inkSpin->setValue(obj.getInkLevel());
    } else {
        m_inkSpin->setValue(0);
    }

    QMessageBox::information(this, "Импорт", "Данные из TXT загружены в форму. Вы можете их отредактировать.");
}

void Program1Window::onSaveObject()
{
    if (m_currentJsonPath.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Сначала выберите JSON файл.");
        return;
    }

    QString name = m_nameEdit->text().trimmed();
    QString desc = m_descEdit->text().trimmed();
    QString color = m_colorEdit->text().trimmed();
    int ink = m_inkSpin->value();

    InkObject newObj(name, desc, color, ink);
    if (!newObj.isValid()) {
        QMessageBox::warning(this, "Ошибка", "Объект не заполнен или уровень чернил вне диапазона 0-100.\nБитые объекты не сохраняются.");
        return;
    }

    // Добавляем в конец существующего массива
    m_existingArray.append(newObj.toJson());

    // Сохраняем в файл
    QFile file(m_currentJsonPath);
    if (file.open(QIODevice::WriteOnly)) {
        QJsonDocument doc(m_existingArray);
        file.write(doc.toJson());
        file.close();
        QMessageBox::information(this, "Успех", "Объект добавлен в конец JSON файла.");
    } else {
        QMessageBox::critical(this, "Ошибка", "Не удалось сохранить в JSON файл.");
        return;
    }

    // Очищаем поля
    m_nameEdit->clear();
    m_descEdit->clear();
    m_colorEdit->clear();
    m_inkSpin->setValue(0);
}
