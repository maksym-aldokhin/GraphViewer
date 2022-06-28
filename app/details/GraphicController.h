#pragma once

#include <QObject>
#include <QUuid>
#include <QMap>

#include "Graphic.h"

#include <optional>

namespace GraphicViewer {

class GraphicController : public QObject
{
	Q_OBJECT
public:
	virtual std::optional<QUuid> addGraphic(const GraphicPtr &) = 0;
	virtual void removeGraphicById(QUuid) = 0;
	virtual QVector<GraphicPtr> graphics() const = 0;
	virtual QVector<QUuid> graphicsIds() const = 0;
	virtual std::optional<GraphicPtr> getById(QUuid) const = 0;

	virtual void update(const QMap<QString, double> &) = 0;
	virtual void update(const QMap<QUuid, double> &) = 0;

signals:
	void graphicAdded(QUuid id);
	void graphicRemoved(QUuid id);
	void addedData();
};

std::shared_ptr<GraphicController> createGraphicController();

} // GraphicViewer
