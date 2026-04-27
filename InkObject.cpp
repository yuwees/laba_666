#include "InkObject.hpp"
#include <QStringList>

InkObject::InkObject() : m_inkLevel(-1) {}

InkObject::InkObject(const QString &name, const QString &desc, const QString &color, int inkLevel)
    : m_name(name), m_description(desc), m_color(color), m_inkLevel(inkLevel) {}

bool InkObject::isValid() const
{
    return !m_name.isEmpty() && !m_description.isEmpty() && !m_color.isEmpty()
           && m_inkLevel >= 0 && m_inkLevel <= 100;
}

bool InkObject::parseFromTxtLine(const QString &line)
{
    QStringList parts = line.split('/');
    while (parts.size() < 4) parts.append("");
    m_name = parts[0].trimmed();
    m_description = parts[1].trimmed();
    m_color = parts[2].trimmed();
    bool ok;
    int val = parts[3].trimmed().toInt(&ok);
    m_inkLevel = ok ? val : -1;
    return true;
}

QJsonObject InkObject::toJson() const
{
    QJsonObject obj;
    obj["name"] = m_name;
    obj["description"] = m_description;
    obj["color"] = m_color;
    obj["inkLevel"] = m_inkLevel;
    return obj;
}

void InkObject::fromJson(const QJsonObject &obj)
{
    m_name = obj["name"].toString();
    m_description = obj["description"].toString();
    m_color = obj["color"].toString();
    m_inkLevel = obj["inkLevel"].toInt(-1);
}

QString InkObject::getName() const { return m_name; }
QString InkObject::getDescription() const { return m_description; }
QString InkObject::getColor() const { return m_color; }
int InkObject::getInkLevel() const { return m_inkLevel; }

void InkObject::setName(const QString &name) { m_name = name; }
void InkObject::setDescription(const QString &desc) { m_description = desc; }
void InkObject::setColor(const QString &color) { m_color = color; }
void InkObject::setInkLevel(int level) { m_inkLevel = level; }
