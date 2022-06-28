#pragma once

#include "qobjectdefs.h"
#include <QAbstractListModel>
#include <QUuid>
#include <QColor>

namespace GraphicViewer {

class Graphic;
class GraphicController;

namespace ui {

class GraphicsModel : public QAbstractListModel
{
	Q_OBJECT

public:
	enum GraphicsModelRoles {
		NameRole = Qt::UserRole,
		DescriptionRole,
		VisibleRole,
		LastValueXRole,
		LastValueYRole,
		ColorRole,
	};

	explicit GraphicsModel(const std::shared_ptr<GraphicController>& controller,
	                       QObject *parent = nullptr);

	QVariant data(const QModelIndex &index, int role) const override;
	bool setData(const QModelIndex &index, const QVariant &value, int role) override;
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	QHash<int, QByteArray> roleNames() const override;
	Q_INVOKABLE int count() const;
	Q_INVOKABLE int maxDot() const;

signals:
	void newData();
	void visibleChanged();

private:
	void graphicAdded(QUuid id);
	void graphicRemoved(QUuid id);

	struct GraphicItem {
		QUuid id;
		bool visible = true;
		QColor color;
	};

	std::shared_ptr<GraphicController> m_controller;
	QVector<GraphicItem> m_graphics;
};

} // ui

} // GraphicViewer
