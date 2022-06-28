#pragma once

#include <QObject>
#include <QUuid>
#include <QString>

#include <memory>

#include "ValueStorage.h"

namespace GraphicViewer {

class Graphic;

using GraphicPtr = std::shared_ptr<Graphic>;

class Graphic : public QObject
{
	Q_OBJECT

public:
	Graphic(QObject *parent = nullptr);
	Graphic(const QString &name, const QString &description, QObject *parent = nullptr);
	Graphic(const Graphic&);
	Graphic(const Graphic&&);

	void setName(const QString &);
	QString name() const;
	void setDescription(const QString &);
	QString description() const;
	QUuid id() const;

	void addPoint(double);
	ValueStorage &getValueStorage();

signals:
	void nameChanged(const QString &name);
	void descriptionChanged(const QString &description);
	void addedPoint();

private:
	QString m_name;
	QString m_description;
	const QUuid m_id;

	ValueStorage m_valueStorage;
};

bool operator==(const Graphic &r, const Graphic &l);

GraphicPtr createGraphic(const QString &name = "", const QString &description = "");

} // GraphicViewer
