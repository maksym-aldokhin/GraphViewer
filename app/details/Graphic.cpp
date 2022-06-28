#include "Graphic.h"

namespace GraphicViewer {

Graphic::Graphic(QObject *parent)
    : QObject(parent)
    , m_id(QUuid::createUuid())
{

}

Graphic::Graphic(const QString &name, const QString &description, QObject *parent)
    : Graphic(parent)
{
	setName(name);
	setDescription(description);
}

Graphic::Graphic(const Graphic &v)
    : m_name(v.name())
    , m_description(v.description())
    , m_id(v.id())
{
}

Graphic::Graphic(const Graphic &&v)
    : m_name(v.name())
    , m_description(v.description())
    , m_id(v.id())
{

}

void Graphic::setName(const QString &name)
{
	if (m_name == name) {
		return;
	}
	m_name = name;

	emit nameChanged(m_name);
}

QString Graphic::name() const
{
	return m_name;
}

void Graphic::setDescription(const QString &description)
{
	if (m_description == description) {
		return;
	}
	m_description = description;

	emit descriptionChanged(m_description);
}

QString Graphic::description() const
{
	return m_description;
}

QUuid Graphic::id() const
{
	return m_id;
}

void Graphic::addPoint(double v)
{
	m_valueStorage.addPoint(v);

	emit addedPoint();
}

ValueStorage &Graphic::getValueStorage()
{
	return m_valueStorage;
}

bool operator==(const Graphic &r, const Graphic &l)
{
	return r.id() == l.id()
	        && r.name() == l.name()
	        && r.description() == l.description();
}

GraphicPtr createGraphic(const QString &name, const QString &description)
{
	return std::make_shared<Graphic>(name, description);
}

}
