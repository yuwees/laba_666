#ifndef INKOBJECT_HPP
#define INKOBJECT_HPP

#include <QString>
#include <QJsonObject>

class InkObject
{
public:
    InkObject();
    InkObject(const QString &name, const QString &desc, const QString &color, int inkLevel);

    bool isValid() const;
    bool parseFromTxtLine(const QString &line);

    QJsonObject toJson() const;
    void fromJson(const QJsonObject &obj);

    QString getName() const;
    QString getDescription() const;
    QString getColor() const;
    int getInkLevel() const;

    void setName(const QString &name);
    void setDescription(const QString &desc);
    void setColor(const QString &color);
    void setInkLevel(int level);

private:
    QString m_name;
    QString m_description;
    QString m_color;
    int m_inkLevel;
};

#endif // INKOBJECT_HPP
